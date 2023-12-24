#include "Emitter.h"
#include "utf8.h"

namespace hoo {
llvm::Value* Emitter::lookupVariable(const std::string& name) {
    return this->symbolTable->lookupVariable(name);
}

std::shared_ptr<llvm::IRBuilder<>> Emitter::createBuilder() {
    if (currentBlock) {
        return std::make_shared<llvm::IRBuilder<>>(currentBlock);
    } else if (currentFunction) {
        return std::make_shared<llvm::IRBuilder<>>(currentFunction->getEntryBlock().getFirstNonPHI());
    } else {
        return std::make_shared<llvm::IRBuilder<>>(context);
    }
}

llvm::Value* Emitter::emitByteConstant(uint8_t value) {
    return createBuilder()->getInt8(value);
}

llvm::Value* Emitter::emitIntegerConstant(int64_t value) {
    return createBuilder()->getInt64(value);
}

llvm::Value* Emitter::emitCharConstant(const std::string& value) {
    std::vector<uint8_t> utf8Bytes;
    utf8::utf8to32(value.begin(), value.end(), back_inserter(utf8Bytes));
    std::vector<llvm::Constant*> byteConstants;
    for (uint8_t byte : utf8Bytes) {
        byteConstants.push_back(llvm::ConstantInt::get(llvm::Type::getInt8Ty(context), byte));
    }
    auto builder = createBuilder();
    llvm::ArrayType* byteArrayType = llvm::ArrayType::get(llvm::Type::getInt8Ty(context), byteConstants.size());
    llvm::Constant* byteArray = llvm::ConstantArray::get(byteArrayType, byteConstants);
    return builder->CreateAlloca(byteArrayType, nullptr, "char_constant");
}

llvm::Value* Emitter::emitBooleanConstant(bool value) {
    return createBuilder()->getInt1(value);
}

llvm::Value* Emitter::emitDoubleConstant(double value) {
    return llvm::ConstantFP::get(context, llvm::APFloat(value));
}

llvm::Value* Emitter::emitStringConstant(const std::string& value) {
    std::vector<uint8_t> utf8Bytes;
    utf8::utf8to32(value.begin(), value.end(), back_inserter(utf8Bytes));

    // Add null terminator
    utf8Bytes.push_back(0);

    std::vector<llvm::Constant*> byteConstants;
    for (uint8_t byte : utf8Bytes) {
        byteConstants.push_back(llvm::ConstantInt::get(llvm::Type::getInt8Ty(context), byte));
    }

    auto builder = createBuilder();
    llvm::ArrayType* byteArrayType = llvm::ArrayType::get(llvm::Type::getInt8Ty(context), byteConstants.size());
    llvm::Constant* byteArray = llvm::ConstantArray::get(byteArrayType, byteConstants);
    return builder->CreateAlloca(byteArrayType, nullptr, "string_constant");  // Use CreateAlloca for string constants
}

}
