#ifndef EMITTER_H
#define EMITTER_H

#include <memory>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"

#include "SymbolTable.h"

namespace hoo {
class Emitter {
public:
    Emitter(llvm::LLVMContext& context, llvm::Module& module) : context(context),
    module(module),
    symbolTable(std::make_shared<SymbolTable>()) {}

    void setCurrentBlock(llvm::BasicBlock* block) { currentBlock = block; }
    void setCurrentFunction(llvm::Function* function) { currentFunction = function; }
    llvm::Value* lookupVariable(const std::string& name);

    llvm::Value* emitByteConstant(uint8_t value);
    llvm::Value* emitIntegerConstant(int64_t value);
    llvm::Value* emitCharConstant(const std::string& value);
    llvm::Value* emitBooleanConstant(bool value);
    llvm::Value* emitDoubleConstant(double value);
    llvm::Value* emitStringConstant(const std::string& value);

private:
    llvm::LLVMContext& context;
    llvm::Module& module;
    llvm::BasicBlock* currentBlock = nullptr;
    llvm::Function* currentFunction = nullptr;
    std::shared_ptr<SymbolTable> symbolTable;

    std::shared_ptr<llvm::IRBuilder<>> createBuilder();
};
}

#endif
