#ifndef NANLER_COMPILER_HPP
#define NANLER_COMPILER_HPP

#include "lexer.hpp"
#include "mewtypes.h"
#include <unordered_map>
#include "virtual.hpp"
#include "Config.hpp"

namespace nanler::compiler {
  struct Stack;

  u64 GetLastSize(Stack& st);
  
  // do line
  void DoLine(Stack& st, Context* ctx);
  // do expr
  void DoExpression(Stack& st, Context* ctx);
  // do assign
  void DoAssign(Stack& st, AssignContext* ctx);
  // process block as isolate unnamed auto call 'function'
  void DoBlock(Stack& st, BlockContext* ctx);
  // returns value to stack top
  void DoMath(Stack& st, OperatorContext* ctx); 
  // process function call returns is first register r rx fx dx
  void DoCall(Stack& st, FunctionCall* ctx); 
  // incapsualte from '?'
  void DoIncapsulate(Stack& st, IncapsulateContext* ctx); 
  void DoReturn(Stack& st, ReturnContext* ctx); 
  void DoConditionalBlock(Stack& st, IfContext* ctx);
  // puts 'raw' binary code
  void DoBin(Stack& st, BinContext* ctx);
  void CallInlineFunction(Stack& st, FunctionDeclaration* fd, SquareArray* argsin);

  // todo not implemented
  // void DoTrait(Stack& st, TraitContext* ctx);
  // void DoTypedef(Stack& st, TypeContext* ctx);

  struct OperatorHandler {
    ContextType signature;
    enum struct OperatorType {
      Left,
      Right,
      Both
    } type;
    u8 l_important = 0;
    u8 r_important = 0;
    FunctionDeclaration* handler;
  };
  
  struct Function {
    FunctionDeclaration* ref;
    u64 offset;
    Function() {}
    Function(FunctionDeclaration* ref, u64 offset)
      : ref(ref), offset(offset) {}
  };
  
  struct StackVariable {
    AssignContext* ref;
    u64 size;
    u64 offset;

    StackVariable() {}
    StackVariable(u64 size, u64 offset, AssignContext* ref = nullptr)
      : ref(ref), size(size), offset(offset) {}

    bool is_empty() const noexcept {
      return ref == nullptr;
    }
  };

  struct StackHandler {
    std::unordered_map<const char*, StackVariable*> variables;
    mew::stack<StackVariable*> stack;
    u64 last_offset = 0;

    void putVariableRaw(const char* name, u64 size, AssignContext* ctx, Virtual::CodeBuilder& cb, Stack& st, Context* value) {
      DoExpression(st, value);
      u64 out_size = GetLastSize(st);
      auto sv = new StackVariable(size, last_offset, ctx);
      variables.insert({name, sv});
      stack.push(sv);
      u64 offset = size;                // calculate offset
      // normalize size
      if (size > out_size)
        for (u64 i = 0; i < size - out_size; ++i)
        (cb
          << Virtual::Instruction_PUSH  
          << Virtual::Instruction_BYTE   // push struct type
          << 0               
        );
      (cb
        << Virtual::Instruction_PUSH  
        << Virtual::Instruction_STRUCT // push struct type
        << Virtual::Instruction_ST     // push from stack
        << size                        // offset
        << size                        // size
      );

      last_offset += size;
    }

    bool findEmptyPlace(const char* name, u64 size, AssignContext* ctx, Virtual::CodeBuilder& cb, Stack& st, Context* value) {
      for (int i = 0; i < stack.count(); ++i) {
        auto e = stack.at(i);
        if (e->is_empty() && e->size >= size) {
          // todo splitting & merging;
          putVariableRaw(name, size, ctx, cb, st, value);
          return true;
        }
      }
      return false;
    }
    
    bool findEmptyPlace(const char* name, u64 size, AssignContext* ctx, Virtual::CodeBuilder& cb, Stack& st, Context* value) {
      for (int i = 0; i < stack.count(); ++i) {
        auto e = stack.at(i);
        if (e->is_empty() && e->size >= size) {
          // todo splitting & merging;
          putVariableRaw(name, size, ctx, cb, st, value);
          return true;
        }
      }
      return false;
    }
    
    void put(AssignContext* ctx, Virtual::CodeBuilder& cb, Stack& st) {
      const char* name = ctx->parseName();
      u64 size = ctx->parseSize();
      if (findEmptyPlace(name, size, ctx, cb, st, ctx->value->get<ExpressionContext>()->row)) {return;}
      putVariableRaw(name, size, ctx, cb, st, ctx->value->get<ExpressionContext>()->row);
    }
    
    void put(AssignContext* ctx, Virtual::CodeBuilder& cb, Stack& st, Context* value) {
      const char* name = ctx->parseName();
      u64 size = ctx->parseSize();
      if (findEmptyPlace(name, size, ctx, cb, st, value)) {return;}
      putVariableRaw(name, size, ctx, cb, st, value);
    }

    void clearVariable(const char* name, Virtual::CodeBuilder& cb) {
      auto it = variables.find(name);
      MewUserAssert(it != variables.end(), "can't find variable");
      auto var = it->second;
      (cb // clear to zero
        << Virtual::Instruction_PUSH  
        << Virtual::Instruction_ST
        << var->offset
        << Virtual::Instruction_NUM
        << 0
      );
      var->name = 0;
      var->ref  = 0;
    }
    
  };

  struct HeapVariable {
    u64 offset;
  };

  struct Stack {
    Virtual::CodeBuilder cb;
    mew::stack<OperatorHandler> operators;
    // std::unordered_map<const char*, u64> template_types;
    StackHandler stack_handler;
    bool has_return = false;
    u64 template_size = 0;
    
    std::unordered_map<const char*, Function*> functions;
    std::unordered_map<const char*, HeapVariable*> heap;

    void putFunction(FunctionDeclaration* fd) {
      u64 cursor = cb.cursor();
      const char* name = fd->parseName();
      functions.insert({name, Function( fd, cursor)});
    }
    
    void putVariable(AssignContext* ctx) {
      const char* name = ctx->parseName();
      stack_handler.put(ctx, cb);
    }

    Function& getFunctionAddress(const char* name) {
      auto it = functions.find(name);
      MewUserAssert(it != functions.end(), "Cannot find function");
      return it->second;
    }

    HeapVariable& getHeapVariableAddress(const char* name) {
      auto it = heap.find(name);
      MewUserAssert(it != heap.end(), "Cannot find function");
      return it->second;
    }

    void putOperator(OperatorDeclaration* fd) {
      OperatorHandler op;
      op.signature = fd->name->type;
      op.type = (OperatorHandler::OperatorType)fd->operator_type;
      op.handler = fd->handler;
      op.l_important = fd->l_important;
      op.r_important = fd->r_important;
      operators.push(op);
    }

    OperatorHandler* findOperator(ContextType type, OperatorHandler::OperatorType op_type) {
      for (int i = 0; i < operators.count(); ++i) {
        auto& op = operators[i];
        if (op.signature == type && op.type == op_type) {
          return &op;
        }
      }
      return nullptr;
    }

  };

  class Compiler {
  private:
    Stack _m_stack;
  public:
    Compiler() {}
    
    Stack& operator*() {
      return _m_stack;
    }

    Stack& st() {
      return _m_stack;
    }


  };

  u64 GetLastSize(Stack& st) {
    return st.template_size;
  }


  void CallInlineFunction(Stack& st, FunctionDeclaration* fd, SquareArray* argsin) {  // Complete. NT
    auto type = fd->return_type;
    auto args = fd->args.args;
    u64 stack_before = st.stack_handler.stack.count();
    // adds local variables
    for (int i = 0; i < args.count(); ++i) {
      auto arg = args.at(i)->get<AssignContext>();
      auto val = argsin->args.at(i)->get<ExpressionContext>()->row;
      st.stack_handler.put(arg, st.cb, st, val);
    }
    // execute function body
    for (int i = 0; i < fd->content.lines.count(); ++i) {
      DoLine(st, fd->content.lines[i]);
    }

    mew::stack<StackVariable*> after = st.stack_handler.stack.shiftAfter(stack_before);
    auto count = after.count() - st.has_return;
    // removing local variable from block
    for (int i = 0; i < count; ++i) {
      auto unit = after.at(i);
      st.stack_handler.clearVariable(unit->ref->parseName(), st.cb);
    }
    st.stack_handler.stack.erase(stack_before, count);
  }

	void DoLine(Stack &st, Context *ctx) { // TODO!

	}

	void DoExpression(Stack &st, Context *ctx) // Complete. NT
	{
		st.template_size = 0;
    switch (ctx->type) {
      case ContextType::AssignContext:
        DoAssign(st, ctx->get<AssignContext>());
        break;
      case ContextType::BlockContext:
        DoBlock(st, ctx->get<BlockContext>());
        break;
      case ContextType::OperatorContext:
        DoMath(st, ctx->get<OperatorContext>());
        break;
      case ContextType::FunctionCall:
        DoCall(st, ctx->get<FunctionCall>());
        break;
      case ContextType::IncapsulateContext:
        DoIncapsulate(st, ctx->get<IncapsulateContext>());
        break;
      case ContextType::ReturnContext:
        DoReturn(st, ctx->get<ReturnContext>());
        break;
      case ContextType::IfContext:
        DoConditionalBlock(st, ctx->get<IfContext>());
        break;
      case ContextType::BinContext:
        DoBin(st, ctx->get<BinContext>());
        break;
      default:
        MewUserAssert(false, "Unsupported expression context type");
    }
	}

	void DoAssign(Stack& st, AssignContext* ctx) { // Complete. NT
    u64 size = ParseTypeSize(ctx->type);
    st.stack_handler.put(ctx, st.cb);
  }
  
  void DoBlock(Stack& st, BlockContext* ctx) { // Complete. NT
    // store 
    u64 stack_before = st.stack_handler.stack.count();
    // execute
    for (int i = 0; i < ctx->lines.count(); ++i) {
      DoLine(st, ctx->lines[i]);
    }
    mew::stack<StackVariable*> after = st.stack_handler.stack.shiftAfter(stack_before);
    auto count = after.count() - st.has_return;
    // removing local variable from block
    for (int i = 0; i < count; ++i) {
      auto unit = after.at(i);
      st.stack_handler.clearVariable(unit->ref->parseName(), st.cb);
    }
    st.stack_handler.stack.erase(stack_before, count);
  }
  
  void DoMath(Stack& st, OperatorContext* ctx) { // Complete. Has TODO`s
    OperatorHandler::OperatorType op_type; // create formula
    if (ctx->left == nullptr) {
      op_type = OperatorHandler::OperatorType::Right;
    } else if (ctx->right == nullptr) {
      op_type = OperatorHandler::OperatorType::Left;
    } else {
      op_type = OperatorHandler::OperatorType::Both;
    }

    auto op = st.findOperator(ctx->operator_type, op_type);
    MewUserAssert(op != nullptr, "Cannot find operator handler");
    // todo important usage
    auto argsin = new SquareArray(); 
    if (ctx->left)
      argsin->args.push(ctx->left);
    if (ctx->right)
      argsin->args.push(ctx->right);
    CallInlineFunction(st, op->handler, argsin);
    delete argsin;
  }
  
  void DoCall(Stack& st, FunctionCall* ctx) {

  }
  
  void DoIncapsulate(Stack& st, IncapsulateContext* ctx) {

  }
  
  void DoReturn(Stack& st, ReturnContext* ctx) {

  }
  
  void DoConditionalBlock(Stack& st, IfContext* ctx) {

  }
  
  void DoBin(Stack& st, BinContext* ctx) {
    
  }
  
};

#endif