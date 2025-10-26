#ifndef NANASM_COMPILER_HPP
#define NANASM_COMPILER_HPP

#include "mewtypes.h"
#include "mewlib.h"
#include <unordered_map>
#include "virtual.hpp"
#include <unordered_map>
#include "mewutils.hpp"

namespace nanasm {
  enum struct TokenType {
    Undefined,
    LABEL,
    R1,  R2,	R3,	 R4,  R5,
    RX1, RX2, RX3, RX4, RX5,
    DX1, DX2, DX3, DX4, DX5,
    FX1, FX2, FX3, FX4, FX5,
    RDI, NUMBER, BYTE, WORD,
    DATA, STRING, ARRAY, NAMED_ADDRESS,
    COMMA,
    PUSHN, PUSHM, PUSHB, PUSHR, PUSH,
    POP, POPR,
    CALL, CALLE,
    ADD, SUB, MUL, DIV, INC, DEC, NOT, XOR, OR, AND, LS, RS,
    JMP, RET, EXIT, TEST, JE, JEL, JEM, JNE, JL, JM, MOV, SWAP, MSET, MSET, 
    PUTC, PUTI, PUTI, PUTS, GETCH,
    WINE, OPEN, MOV, WRITE, READ, CLOSE, 
  };

  static std::unordered_map<const char *, TokenType> token_semantic = {
    {"r1", TokenType::R1},
    {"r2", TokenType::R2},
    {"r3", TokenType::R3},
    {"r4", TokenType::R4},
    {"r5", TokenType::R5},
    {"fx1", TokenType::FX1},
    {"fx2", TokenType::FX2},
    {"fx3", TokenType::FX3},
    {"fx4", TokenType::FX4},
    {"fx5", TokenType::FX5},
    {"dx1", TokenType::DX1},
    {"dx2", TokenType::DX2},
    {"dx3", TokenType::DX3},
    {"dx4", TokenType::DX4},
    {"dx5", TokenType::DX5},
    {"rx1", TokenType::RX1},
    {"rx2", TokenType::RX2},
    {"rx3", TokenType::RX3},
    {"rx4", TokenType::RX4},
    {"rx5", TokenType::RX5},
    {"data", TokenType::DATA},
    {",", TokenType::COMMA},
    {"pushn", TokenType::PUSHN},
    {"pushm", TokenType::PUSHM},
    {"pushb", TokenType::PUSHB},
    {"pushr", TokenType::PUSHR},
    {"push", TokenType::PUSH},
    {"pop", TokenType::POP},
    {"popr", TokenType::POPR},
    {"call", TokenType::CALL},
    {"calle", TokenType::CALLE},
    {"add", TokenType::ADD},
    {"sub", TokenType::SUB},
    {"mul", TokenType::MUL},
    {"div", TokenType::DIV},
    {"inc", TokenType::INC},
    {"dec", TokenType::DEC},
    {"not", TokenType::NOT},
    {"xor", TokenType::XOR},
    {"or", TokenType::OR},
    {"and", TokenType::AND},
    {"ls", TokenType::LS},
    {"rs", TokenType::RS},
    {"jmp", TokenType::JMP},
    {"ret", TokenType::RET},
    {"exit", TokenType::EXIT},
    {"test", TokenType::TEST},
    {"je", TokenType::JE},
    {"jel", TokenType::JEL},
    {"jem", TokenType::JEM},
    {"jne", TokenType::JNE},
    {"jl", TokenType::JL},
    {"jm", TokenType::JM},
    {"mov", TokenType::MOV},
    {"swap", TokenType::SWAP},
    {"mset", TokenType::MSET},
    {"mset", TokenType::MSET},
    {"putc", TokenType::PUTC},
    {"puti", TokenType::PUTI},
    {"puti", TokenType::PUTI},
    {"puts", TokenType::PUTS},
    {"getch", TokenType::GETCH},
    {"wine", TokenType::WINE},
    {"open", TokenType::OPEN},
    {"mov", TokenType::MOV},
    {"write", TokenType::WRITE},
    {"read", TokenType::READ},
    {"close", TokenType::CLOSE},

  };

  struct DataValue {
    u8* value; // string or array of bytes
    u64 size;
  };

  struct DataViewValue {
    u64 offset;
    u64 size;
  };

  struct Token {
    TokenType type;
    u8* value;
  };

  Token* GetTokenFromTable(const char* word) {
		bool is_find = false;
		for (auto it = token_semantic.begin(); it != token_semantic.end(); ++it) {
			if (mew::strcmp(it->first, word)) {
				Token* tk = new Token;
				tk->type = it->second;
        tk->value = nullptr;
        return tk;
			}
		}
		return nullptr;
	}

  
  struct Lexer {
    mew::stack<Token> tokens;

    void parse(const char* source) {
      using namespace mew::utils;
      TokenRow str_row(source);
      str_row.SkipToStart();
      const char* word;
      while ((word = *str_row++) != nullptr && *word != '\0') { 
        Token* _from_table = GetTokenFromTable(word);
        if (_from_table != nullptr) {
          tokens.push(_from_table);
          continue;
        }
        if (mew::starts_with(word, "rdi")) { 
          Token rdi_tk = {
            .type = TokenType::RDI,
            .value = strlen(word) == 3 ? 0: (u8*)mew::stoi(word+3)
          };
          tokens.push(rdi_tk);
          continue;
        }
        
        if (word[0] == '[') {
          mew::stack<u8> temp;
          while((word = *str_row++) != nullptr && *word != '\0' && word[0] != ']' ) {
            if (word[0] == ',') continue;
            bool success;
            u8 val = (u8)mew::str_to_int(word, success);
            MewUserAssert(success, "invalid byte value in array");
            temp.push(val);
          }
          auto val = new DataValue();
          val->size = temp.count();
          val->value = (u8*)rcopy(temp.begin(), temp.count());
          Token arr_tk = {
            .type = TokenType::ARRAY,
            .value = (byte*)val
          };
          tokens.push(arr_tk);
          continue;
        }
        
        const char* temp = word;
        const char* next = str_row.Current();
        if (next != nullptr && *next != '\0' && *next == ':' ) {
          Token label_tk = {
            .type = TokenType::LABEL,
            .value = (u8*)scopy(temp)
          };
          tokens.push(label_tk);
          ++str_row;
          continue;
        }
        if (temp[0] == "&" && next != nullptr && *next != '\0') {
          Token named_addr_tk = {
            .type = TokenType::NAMED_ADDRESS,
            .value = (u8*)scopy(next)
          };
          tokens.push(named_addr_tk);
          ++str_row;
          continue;
        }
        
        Token tk = {
          .type = TokenType::Undefined,
          .value = scopy(word)
        };
        tokens.push(tk);
      }
    }

    void WatchUndefinedTokens(Token& tk) {
      bool success;
      auto number = mew::utils::str_to_int(tk.value, success);
      if (success) {
        tk.type = TokenType::NUMBER;
        tk.value = (u8*)number;
      }
      if (*tk.value == '"' && getLastChar(tk.value) == '"') {
        tk.type = TokenType::STRING;
        mew::utils::fas(tk.value, (const char*)str_parse(tk.value+1, strlen(tk.value)-2));
        return;
      }
      tk.type = TokenType::WORD;
    }

    void DecryptUndefinedTokens() {
      for (int x = 0; x < tokens.count(); ++x) {
        auto& e = tokens[x];
        if (e.type == TokenType::Undefined) {
          WatchUndefinedTokens(e);
        }
      }
    }
    
    void Tokenize(const char* src) {
      parse(src);
      DecryptUndefinedTokens();
    }
  };

  struct Compiler {
    Virtual::CodeBuilder cb;
    std::unordered_map<const char*, DataViewValue> data;
    std::unordered_map<u64, DataViewValue> data_calles; // <where, ...>
    std::unordered_map<const char*, u64> label;
    std::unordered_map<u64, u64> calles; // <at_code, target_offset> -- jump & call & j<?>
    std::unordered_map<const char*, u64> external_calles;
    u64 pos = 0;

    const char* GetAdditionalData() {
      mew::string::StringBuilder cb;
      cb += "MANIFEST";
      cb += "DATA";
      cb += data.size();
      for (auto [k, w]: data) {
        cb += k; cb += '\0';
        cb.AppendStruct(w);
      }
      cb += "CDAT";
      cb += data_calles.size();
      for (auto [k, w]: data_calles) {
        cb += k;
        cb.AppendStruct(w);
      }
      cb += "LBL";
      cb += label.size();
      for (auto [k, w]: label) {
        cb += k; cb += '\0';
        cb += w;
      }
      cb += "CLL";
      cb += calles.size();
      for (auto [k, w]: calles) {
        cb += k;
        cb += w;
      }
      cb += "EXT";
      cb += external_calles.size();
      for (auto [k, w]: external_calles) {
        cb += k; cb += '\0';
        cb += w;
      }
      cb += "END";
      return cb.c_str();
    }

    u64 ReadAdditionalData(char* src) {
      MewUserAssert(mew::starts_with(src, "MANIFEST"), "cannot file debug-manifest");
      src += 9;

      MewUserAssert(mew::starts_with(src, "DATA"), "cannot file DATA SECTION");
      src += 4;
      u64 _size;
      memcpy(&_size, src, sizeof(_size)); src += sizeof(_size);
      for (u64 i = 0; i < _size; ++i) {
        const char* key = scopy(src); src += sizeof(key)+1; 
        DataViewValue* dvv = (DataViewValue*)src; src += sizeof(*dvv);
        data.insert({key, dvv});
      }
      
      MewUserAssert(mew::starts_with(src, "CDAT"), "cannot file CDAT SECTION");
      src += 4;
      memcpy(&_size, src, sizeof(_size)); src += sizeof(_size);
      for (u64 i = 0; i < _size; ++i) {
        u64 key;
        memcpy(&key, src, sizeof(key)); src += sizeof(key);
        DataViewValue* dvv = (DataViewValue*)src; src += sizeof(*dvv);
        data_calles.insert({key, dvv});
      }

      MewUserAssert(mew::starts_with(src, "LBL"), "cannot file LBL SECTION");
      src += 3;
      memcpy(&_size, src, sizeof(_size)); src += sizeof(_size);
      for (u64 i = 0; i < _size; ++i) {
        const char* key = scopy(src); src += sizeof(key)+1; 
        u64 offset;
        memcpy(&offset, src, sizeof(offset)); src += sizeof(offset);
        label.insert({key, offset});
      }

      MewUserAssert(mew::starts_with(src, "CLL"), "cannot file CLL SECTION");
      src += 3;
      memcpy(&_size, src, sizeof(_size)); src += sizeof(_size);
      for (u64 i = 0; i < _size; ++i) {
        u64 key;
        memcpy(&key, src, sizeof(key)); src += sizeof(key);
        u64 offset;
        memcpy(&offset, src, sizeof(offset)); src += sizeof(offset);
        calles.insert({key, offset});
      }
      MewUserAssert(mew::starts_with(src, "EXT"), "cannot file EXT SECTION");
      src += 3;
      memcpy(&_size, src, sizeof(_size)); src += sizeof(_size);
      for (u64 i = 0; i < _size; ++i) {
        const char* key = scopy(src); src += sizeof(key)+1; 
        u64 offset;
        memcpy(&offset, src, sizeof(offset)); src += sizeof(offset);
        external_calles.insert({key, offset});
      }
      MewUserAssert(mew::starts_with(src, "END"), "cannot file END SECTION");
      src += 3;
      return strlen(src);
    }

    Token& Current() {
      return lexer.tokens.at(pos);
    }

    Token& Next() {
      if (lexer.tokens.count() >= ++pos) pos = lexer.tokens.count()-1;
      return Current();
    }

    bool isEnd() {
      return lexer.tokens.count() >= pos;
    }

    Token& Prev() {
      if (0 >= -pos) pos = 0;
      return Current();
    }
    
    u64 GetFunctionAddress(Token& tk) {
      const char* name = (const char*)tk.value;
      auto fd = label.find(name);
      MewUserAssert(fd != label.end(), "Cannot find data");
      calles.insert({cursor()-sizeof(u64), fd->second});
      return fd->second;
    }

    DataViewValue GetNameAddress(Token& tk) {
      const char* name = (const char*)tk.value;
      auto fd = data.find(name);
      MewUserAssert(fd != data.end(), "Cannot find data");
      return fd->second;
    }

    inline bool isRegister(Token& tk) {
      return (u64)tk.type >= (u64)TokenType::R1 && (u64)tk.type <= (u64)TokenType::FX5;
    }

    Virtual::VM_REG_INFO GetRegInfo(Token& tk) {
      Virtual::VM_REG_INFO reg;
      reg.idx = ((u64)tk.type - (u64)TokenType::R1) % 5; 
      reg.type = (Virtual::VM_RegType)(((u64)tk.type - (u64)TokenType::R1) % 4) + 1;
      return reg;
    }

    void PutArg(Token& tk) {
      if (isRegister()) {
        cb.putRegister(getRegInfo());
        return;
      }
      switch(tk.type) {
        case TokenType::NAMED_ADDRESS: {
          auto dvv = GetNameAddress();
          data_calles.insert({cb.cursor(), dvv});
          cb.putMem(dvv.offset, dvv.size);
        } break;
        case TokenType::NUMBER: {
          cb.putNumber((s32)tk.value);
        } break;
        case TokenType::RDI: {
          cb.putRdiOffset((s32)tk.value);
        } break;
        default: MewUserAssert(false, "NOT FOR VM_ARG");
      }
    }

    void compiler(Lexer& lexer) {
      for (Token& tk = Current(); isEnd(); tk = Next()) {
        switch(tk.type) {
          case TokenType::DATA: {
            tk = Next();
            MewUserAssert(tk.type == TokenType::WORD, "data <name> STRING | Byte Array | Number");
            const char* name = tk.value;
            tk = Next();
            MewUserAssert(tk.type == TokenType::STRING || tk.type == TokenType::ARRAY || tk.type == TokenType::NUMBER, "data <name> STRING | Byte Array | Number");
            DataViewValue dvv;
            dvv.offset = cb.data_size();
            switch (tk.type) {
              case TokenType::STRING:
                dvv.size = strlen(tk.value);
                data.insert({name, dvv});
                cb.AddData(tk.value, dvv.size);
              break;
              case TokenType::ARRAY:
                auto dv = (DataValue*)tk.value;
                dvv.size = dv->size;
                data.insert({name, dvv});
                cb.AddData(dv->value, dv->size);
              break;
              case TokenType::NUMBER:
                dvv.size = sizeof(u32);
                data.insert({name, dvv});
                cb.AddData(tk.value, sizeof(u32));
              break;
            }
          } break;
          case TokenType::LABEL: {
            if (!label.contains("end-entry")) {
              if (label.contains("entry")) {
                label.insert({"end-entry", cb.cursor()});
              } else {
                label.insert({"entry", cb.cursor()});
              }
            }
            label.insert({(const char*)tk.value, cb.cursor()});
          } break;
#pragma region PUSH
          case TokenType::PUSHN: {
            cb << Virtual::Instruction_PUSH;
            tk = Next();
            PutArg(tk);
          } break;
          case TokenType::PUSHM: {
            cb << Virtual::Instruction_PUSH;
            tk = Next();
            u64 dest;
            u64 size;
            if (tk.type == TokenType::NUMBER) {
              dest = (u64)tk.value;
              tk = Next();
              size = (u64)tk.value;
            } else if (tk.type == TokenType::NAMED_ADDRESS) {
              auto na = GetNameAddress(tk);
              dest = na.offset;
              size = na.size;
              tk = Next();
            } else {
              MewUserAssert(false, "invalid pushm arg");
            }
            cb.putMem(dest, size);
          } break;
          case TokenType::PUSHB: {
            cb << Virtual::Instruction_PUSH;
            tk = Next();
            MewUserAssert(tk.type == TokenType::NUMBER);
            u8 dest = (u8)(u64)tk.value;
            cb.putByte(dest);
          } break;
          case TokenType::PUSHR: {
            cb << Virtual::Instruction_PUSH;
            tk = Next();
            auto ri = GetRegInfo(tk);
            cb.putRegister(ri);
          } break;
          case TokenType::PUSH: {
            cb << Virtual::Instruction_PUSH;
            auto arg = (tk = Next());
            tk = Next(); // Skip Comma;
            if (tk.type == TokenType::COMMA) {
              tk = Next();
            }
            auto offset = tk;
            MewUserAssert(offset.type == TokenType::NUMBER);
            cb << ((u64)offset.value);
            PutArg(arg);
          } break;
#pragma endregion PUSH
#pragma region POP
          case TokenType::POP: {
            cb << Virtual::Instruction_POP;
          } break;
          case TokenType::POPR: {
            cb << Virtual::Instruction_RPOP;
            tk = Next();
            auto ri = GetRegInfo(tk);
            cb.putRegister(ri);
          } break;

          case TokenType::CALL: {
            cb << Virtual::Instruction_CALL;
            tk = Next();
            u64 offset = GetFunctionAddress(tk);
            cb.putU64(offset);
          } break;

          case TokenType::CALLE: {
            cb << Virtual::Instruction_CALL;
            tk = Next();
            external_calles.insert({(const char*)tk.value, cursor()});
            cb.putU64(0);
          } break;
#pragma endregion POP
#pragma region MATH
          case TokenType::ADD: {
            cb << Virtual::Instruction_ADD;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::SUB: {
            cb << Virtual::Instruction_SUB;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::MUL: {
            cb << Virtual::Instruction_MUL;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::DIV: {
            cb << Virtual::Instruction_DIV;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::INC: {
            cb << Virtual::Instruction_INC;
            PutArg(tk=Next());
          } break;
          case TokenType::DEC: {
            cb << Virtual::Instruction_DEC;
            PutArg(tk=Next());
          } break;
          case TokenType::NOT: {
            cb << Virtual::Instruction_NOT;
            PutArg(tk=Next());
          } break;
          case TokenType::XOR: {
            cb << Virtual::Instruction_XOR;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::OR: {
            cb << Virtual::Instruction_OR;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::AND: {
            cb << Virtual::Instruction_AND;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::LS: {
            cb << Virtual::Instruction_LS;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::RS: {
            cb << Virtual::Instruction_RS;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
#pragma endregion MATH
#pragma region LOGIC
          case TokenType::JMP: {
            cb << Virtual::Instruction_JMP;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          case TokenType::RET: {
            cb << Virtual::Instruction_RET;
          } break;
          case TokenType::EXIT: {
            cb << Virtual::Instruction_EXIT;
          } break;
          case TokenType::TEST: {
            cb << Virtual::Instruction_TEST;
          } break;
          case TokenType::JE: {
            cb << Virtual::Instruction_JE;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          case TokenType::JE: {
            cb << Virtual::Instruction_JE;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          case TokenType::JEL: {
            cb << Virtual::Instruction_JEL;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          case TokenType::JEM: {
            cb << Virtual::Instruction_JEM;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          case TokenType::JNE: {
            cb << Virtual::Instruction_JNE;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          case TokenType::JL: {
            cb << Virtual::Instruction_JL;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          case TokenType::JM: {
            cb << Virtual::Instruction_JM;
            u64 offset = GetFunctionAddress(tk = Next());
            cb.putU64(offset);
          } break;
          
          case TokenType::MOV: {
            cb << Virtual::Instruction_MOV;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::SWAP: {
            cb << Virtual::Instruction_SWAP;
            PutArg(tk=Next());
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
          } break;
          case TokenType::MSET: {
            cb << Virtual::Instruction_MSET;
            tk = Next();
            u64 start, size, value;
            if (tk.type == TokenType::NAMED_ADDRESS) {
              start = GetNameAddress(tk);
            } else if (tk.type == TokenType::NUMBER) {
              start = (u32)tk.value;
            } else {
              MewUserAssert(false, "discard arg for mset[0]");
            }
            tk = Next();
            MewUserAssert(tk.type == TokenType::NUMBER, "discard arg for mset[1]");
            size = (u32)tk.value;
            tk = Next();
            MewUserAssert(tk.type == TokenType::NUMBER, "discard arg for mset[2]");
            value = (u32)tk.value;
            cb.putU64(start).putU64(size).putU64(value);
          } break;
#pragma endregion LOGIC
#pragma region ETC
          case TokenType::PUTC: {
            cb << Virtual::Instruction_PUTC;
            tk = Next();
            MewUserAssert(tk.type == TokenType::NUMBER, "discard arg for putc");
            u16 _s = (u16)(s32)tk.value;
            cb << _s;
          } break;
          case TokenType::PUTI: {
            cb << Virtual::Instruction_PUTI;
            tk = Next();
            PutArg(tk);
          } break;
          case TokenType::PUTS: {
            cb << Virtual::Instruction_PUTS;
            tk = Next();
            if (tk.type == TokenType::NAMED_ADDRESS) {
              cb.putU64(GetNameAddress(tk));
            } else if (tk.type == TokenType::NUMBER) {
              cb.putU64((u32)tk.value);
            } else {
              MewUserAssert(false, "discard arg for puts");
            }
          } break;
          case TokenType::GETCH: {
            cb << Virtual::Instruction_GETCH;
            tk = Next();
            PutArg(tk);
          } break;
#pragma endregion ETC
#pragma region FILE
          case TokenType::WINE: {
            cb << Virtual::Instruction_WINE;
            tk = Next();
            if (tk.type == TokenType::NAMED_ADDRESS) {
              cb.putU64(GetNameAddress(tk));
            } else if (tk.type == TokenType::NUMBER) {
              cb.putU64((u32)tk.value);
            } else {
              MewUserAssert(false, "discard arg for wine");
            }
          } break;
          case TokenType::OPEN: {
            cb << Virtual::Instruction_OPEN;
            tk = Next();
            if (tk.type == TokenType::NAMED_ADDRESS) {
              cb.putU64(GetNameAddress(tk));
            } else if (tk.type == TokenType::NUMBER) {
              cb.putU64((u32)tk.value);
            } else {
              MewUserAssert(false, "discard arg for wine");
            }
          } break;
          case TokenType::WRITE: {
            cb << Virtual::Instruction_WRITE;
            tk = Next();
            PutArg(tk);
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            MewUserAssert(tk.type == TokenType::NUMBER, "discard arg for write[3](size)");
            cb.putU64((u64)(s32)tk.value);
          } break;
          case TokenType::READ: {
            cb << Virtual::Instruction_READ;
            tk = Next();
            PutArg(tk);
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            PutArg(tk);
            tk = Next();
            if (tk.type == TokenType::COMMA) tk = Next(); 
            MewUserAssert(tk.type == TokenType::NUMBER, "discard arg for read[3](size)");
            cb.putU64((u64)(s32)tk.value);
          } break;
          case TokenType::CLOSE: {
            cb << Virtual::Instruction_CLOSE;
            tk = Next();
            PutArg(tk);
          } break;
#pragma endregion FILE
        }
      }
      cb << Virtual::Instruction_EXIT;
      if (!label.contains("end-entry")) {
        label.insert({"end-entry", cb.cursor()});
      }
      if (!label.contains("entry")) {
        label.insert({"entry", 0});
      }
      
    }

    void compile(const char* src) {
      Lexer lexer;
      lexer.Tokenize(src);
      compile(lexer);
    }

    void save(const char* path) {
      Virtual::Isolate::CreateFileIfNotExists(path);
      auto code = *cb;
      Virtual::Code_SaveFromFile(code, path);
    }
    
    void debugSave(const char* path) {
      Virtual::Isolate::CreateFileIfNotExists(path);
      auto code = *cb;
      auto __path = mew::GetAbsPath(path);
      std::ofstream file(__path, std::ios::out | std::ios::binary);
      file.seekp(std::ios::beg);
      const char* debug_manifest = GetAdditionalData();
      file << debug_manifest;
      Virtual::Code_SaveToFile(*code, file);
      file.close(); 
    }

    static Compiler debugRead(const char* path) {
      auto __path = mew::GetAbsPath(path);
      std::ifstream file(__path, std::ios::out | std::ios::binary);
      MewForUserAssert(file.is_open(), "cant open file(%s)", path);
      Compiler comp;
      const char* buffer = mew::ReadFullFile(path);
      u64 offset = comp.ReadAdditionalData(buffer);
      file.seekp((const std::ios_base::seekdir)offset);
      Virtual::Code* code = Virtual::Code_LoadFromFile(file);
      comp.cb = Virtual::CodeBuilder(code);
      file.close();
    }

    static Compiler debugRead(std::ifstream& file) {
      Compiler comp;
      const char* buffer = mew::ReadFullFile(path);
      u64 offset = comp.ReadAdditionalData(buffer);
      file.seekp((const std::ios_base::seekdir)offset);
      Virtual::Code* code = Virtual::Code_LoadFromFile(file);
      comp.cb = Virtual::CodeBuilder(code);
    }
  };

}

#endif