#ifndef NANASM_HPP
#define NANASM_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <stdint.h>
#include "virtual.hpp"

// Define opcode values (minimal set based on Virtual::Instruction)
enum Opcode : uint8_t {
    Instruction_NONE    = 0,
    Instruction_LDLL    = 1,
    Instruction_CALL    = 2,
    Instruction_PUSH    = 3,
    Instruction_POP     = 4,
    Instruction_RPOP    = 5,
    Instruction_ADD     = 6,
    Instruction_SUB     = 7,
    Instruction_MUL     = 8,
    Instruction_DIV     = 9,
    Instruction_INC     = 10,
    Instruction_DEC     = 11,
    Instruction_XOR     = 12,
    Instruction_OR      = 13,
    Instruction_NOT     = 14,
    Instruction_AND     = 15,
    Instruction_LS      = 16,
    Instruction_RS      = 17,
    Instruction_NUM     = 18,
    Instruction_INT     = 19,
    Instruction_FLT     = 20,
    Instruction_DBL     = 21,
    Instruction_UINT    = 22,
    Instruction_BYTE    = 23,
    Instruction_MEM     = 24,
    Instruction_REG     = 25,
    Instruction_HEAP    = 26,
    Instruction_ST      = 27,
    Instruction_JMP     = 28,
    Instruction_RET     = 29,
    Instruction_EXIT    = 30,
    Instruction_TEST    = 31,
    Instruction_JE      = 32,
    Instruction_JEL     = 33,
    Instruction_JEM     = 34,
    Instruction_JNE     = 35,
    Instruction_JL      = 36,
    Instruction_JM      = 37,
    Instruction_MOV     = 38,
    Instruction_SWAP    = 39,
    Instruction_MSET    = 40,
    Instruction_SWST    = 41,
    Instruction_WRITE   = 42,
    Instruction_READ    = 43,
    Instruction_OPEN    = 44,
    Instruction_PUTC    = 45,
    Instruction_PUTI    = 46,
    Instruction_PUTS    = 47,
    Instruction_GETCH   = 48,
    Instruction_MOVRDI  = 49
};

// A relocation record for forward-referenced labels.
struct Relocation {
    size_t pos;            // position in the code buffer to fill (4 bytes)
    std::string label;     // label name
};

// The assembler collects code bytes and data bytes.
class Assembler {
public:
    // output buffers
    std::vector<uint8_t> code;
    std::vector<uint8_t> data;
    // label -> code offset
    std::unordered_map<std::string, size_t> labelTable;
    // list of relocations to fix (for jumps and call operands)
    std::vector<Relocation> relocations;
    // optional entry point offset (set by "entry" directive)
    size_t entryPoint = 0;

    // mapping mnemonics to opcode values
    std::unordered_map<std::string, uint8_t> mnemonicMap{
        {"pop", Instruction_POP},
        {"rpop", Instruction_RPOP},
        {"inc", Instruction_INC},
        {"dec", Instruction_DEC},
        {"gch", Instruction_GETCH},
        {"add", Instruction_ADD},
        {"div", Instruction_DIV},
        {"mul", Instruction_MUL},
        {"sub", Instruction_SUB},
        {"test", Instruction_TEST},
        {"jel", Instruction_JEL},
        {"jem", Instruction_JEM},
        {"je", Instruction_JE},
        {"el", Instruction_JL},   // defined as "el" in nan.g4 for jl
        {"jm", Instruction_JM},
        {"jne", Instruction_JNE},
        {"jmp", Instruction_JMP},
        {"ret", Instruction_RET},
        {"xor", Instruction_XOR},
        {"or", Instruction_OR},
        {"not", Instruction_NOT},
        {"and", Instruction_AND},
        {"ls", Instruction_LS},
        {"rs", Instruction_RS},
        {"mov", Instruction_MOV},
        {"swap", Instruction_SWAP},
        {"mset", Instruction_MSET},
        {"swst", Instruction_SWST},
        {"write", Instruction_WRITE},
        {"read", Instruction_READ},
        {"open", Instruction_OPEN},
        {"putc", Instruction_PUTC},
        {"puti", Instruction_PUTI},
        {"puts", Instruction_PUTS},
        {"push", Instruction_PUSH},
        {"call", Instruction_CALL},
        // "entry" and "data" are directives
    };

    // Helper: trim whitespace from both ends
    static std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    // Helper: split a string by space (simple lexer)
    static std::vector<std::string> split(const std::string& s) {
        std::istringstream iss(s);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token)
            tokens.push_back(token);
        return tokens;
    }

    // Encode a 32-bit integer (little endian) into code at the end of code buffer.
    void emitInt32(int32_t value) {
        uint8_t bytes[4];
        std::memcpy(bytes, &value, 4);
        code.insert(code.end(), bytes, bytes + 4);
    }

    // Process a line from the source file.
    void processLine(const std::string& origLine) {
        std::string line = trim(origLine);
        if (line.empty()) return;
        // if line starts with ';' treat as comment
        if (line[0] == ';')
            return;

        // Label definition: ends with ':'
        if (line.back() == ':') {
            std::string label = line.substr(0, line.size()-1);
            label = trim(label);
            labelTable[label] = code.size();
            return;
        }

        // Directives: "entry" and "data"
        auto tokens = split(line);
        if (tokens.empty()) return;

        if (tokens[0] == "entry") {
            // Syntax: entry labelName --- set entryPoint to label offset.
            if (tokens.size() >= 2) {
                // For now, postpone resolving label reference.
                // Record relocation for entry_point.
                relocations.push_back({ /*pos*/ code.size(), tokens[1] });
                // Emit a dummy int for entry point.
                emitInt32(0);
            }
            return;
        }
        if (tokens[0] == "data") {
            // data directive: syntax: data MOD name (STRING|size_t)
            // We simply append string literal data.
            if (tokens.size() >= 3) {
                // For simplicity, ignore MOD and name.
                // If token[2] starts with '"' then a string literal.
                std::string d = origLine;
                size_t firstQuote = d.find_first_of("\"");
                size_t lastQuote = d.find_last_of("\"");
                if (firstQuote != std::string::npos && lastQuote != std::string::npos && lastQuote>firstQuote) {
                    std::string literal = d.substr(firstQuote+1, lastQuote-firstQuote-1);
                    // Append string (null terminated) to data section.
                    data.insert(data.end(), literal.begin(), literal.end());
                    data.push_back(0);
                }
            }
            return;
        }

        // Otherwise assume it is an instruction.
        // First token is mnemonic.
        std::string mnemonic = tokens[0];
        auto it = mnemonicMap.find(mnemonic);
        if (it == mnemonicMap.end()) {
            std::cerr << "Unknown mnemonic: " << mnemonic << std::endl;
            return;
        }
        uint8_t opcode = it->second;
        // Emit opcode byte.
        code.push_back(opcode);

        // Now process remaining tokens as operands.
        // In nan.g4 many instructions take operands separated by comma.
        // Join remaining tokens (after first) then split by comma.
        if (tokens.size() >= 2) {
            std::string operandStr;
            for (size_t i = 1; i < tokens.size(); i++) {
                operandStr += tokens[i] + " ";
            }
            // Remove commas and split by whitespace.
            std::vector<std::string> ops;
            std::istringstream opStream(operandStr);
            std::string op;
            while (std::getline(opStream, op, ',')) {
                op = trim(op);
                if (!op.empty()) {
                    ops.push_back(op);
                }
            }
            // For each operand, try to parse as integer; if not, assume it is a label.
            for (auto& oper : ops) {
                bool isNumber = true;
                for (char c : oper) {
                    if (!std::isdigit(c) && c != '-' && c != '+') { isNumber = false; break; }
                }
                if (isNumber) {
                    // Emit operand type marker for immediate: use Instruction_NUM (0 or Instruction_NUM)
                    code.push_back(Instruction_NUM);
                    int32_t num = std::stoi(oper);
                    emitInt32(num);
                } else {
                    // If operand in parentheses (register) or other, for simplicity we only support label in jumps.
                    // For jump instructions (jmp, je, etc) a label operand is expected.
                    // Record relocation, emit a placeholder (4 bytes) preceded by immediate marker.
                    code.push_back(Instruction_NUM);
                    relocations.push_back({ code.size(), oper });
                    emitInt32(0); // placeholder
                }
            }
        }
    }

    // After processing all lines, resolve relocations.
    void resolveRelocations() {
        for (auto &rel : relocations) {
            auto it = labelTable.find(rel.label);
            if (it == labelTable.end()) {
                std::cerr << "Undefined label: " << rel.label << std::endl;
                continue;
            }
            int32_t addr = static_cast<int32_t>(it->second);
            std::memcpy(&code[rel.pos], &addr, 4);
        }
    }
};

// Write out binary file in a simple format:
// [version (4 bytes)][code size (4 bytes)][data size (4 bytes)][code bytes][data bytes]
void writeBinaryFile(const std::string& filename, const Assembler& assembler) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Cannot open output file " << filename << std::endl;
        return;
    }
    uint32_t codeSize = assembler.code.size();
    uint32_t dataSize = assembler.data.size();
    int version = VIRTUAL_VERSION;
    // Write version
    ofs.write(reinterpret_cast<const char*>(&version), sizeof(version));
    // Write code size and data size
    ofs.write(reinterpret_cast<const char*>(&codeSize), sizeof(codeSize));
    ofs.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
    // Write code bytes
    ofs.write(reinterpret_cast<const char*>(assembler.code.data()), codeSize);
    // Write data bytes
    ofs.write(reinterpret_cast<const char*>(assembler.data.data()), dataSize);
    ofs.close();
    std::cout << "Compilation successful. Wrote " << codeSize << " code bytes and " 
              << dataSize << " data bytes to " << filename << std::endl;
}

int test() {
    // Use fixed paths: nanasm/test.nsm (input) and nansm/test.nb (output)
    const std::string inputPath = "nanasm/test.nsm";
    const std::string outputPath = "nansm/test.nb";

    std::ifstream ifs(inputPath);
    if (!ifs) {
        std::cerr << "Cannot open input file " << inputPath << std::endl;
        return EXIT_FAILURE;
    }
    Assembler assembler;
    std::string line;
    while (std::getline(ifs, line)) {
        assembler.processLine(line);
    }
    ifs.close();
    
    // Resolve relocations
    assembler.resolveRelocations();
    
    // Write binary file
    writeBinaryFile(outputPath, assembler);
    
    return 0;
}

#endif