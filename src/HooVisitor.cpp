#include "HooVisitor.h"
#include "CompilerError.h"

namespace hoo {
HooVisitor::HooVisitor(llvm::LLVMContext& context, llvm::Module& module) :
context(context),
module(module),
emitter(std::make_unique<Emitter>(context, module)) {
}

antlrcpp::Any HooVisitor::visitLiteralExpression(HooParser::LiteralExpressionContext *ctx) {
    auto literalType = determineLiteralType(ctx);
    llvm::Value* value = nullptr;
    switch (literalType) {
        case ByteLiteral:
            value = emitter->emitByteConstant(ctx->ByteLiteral()->getText()[0]);
            break;
        case IntegerLiteral:
            value = emitter->emitIntegerConstant(std::stoll(ctx->IntegerLiteral()->getText()));
            break;
        case CharLiteral:
            value = emitter->emitCharConstant(ctx->CharLiteral()->getText());
            break;
        case BooleanLiteral:
            value = emitter->emitBooleanConstant(ctx->BooleanLiteral()->getText() == "true");
            break;
        case DoubleLiteral:
            value = emitter->emitDoubleConstant(std::stod(ctx->DoubleLiteral()->getText()));
            break;
        default:
            break;
    }
    return value;
}


antlrcpp::Any HooVisitor::visitStringExpression(HooParser::StringExpressionContext *ctx) {
    std::string stringValue = ctx->StringLiteral()->getText();
    llvm::Value* stringConstant = emitter->emitStringConstant(stringValue);
    return stringConstant;
}

antlrcpp::Any HooVisitor::visitPrimaryExpression(HooParser::PrimaryExpressionContext *ctx) {
    auto literalContext = ctx->literalExpression();
    if (nullptr != literalContext) return visitLiteralExpression(literalContext);
    auto stringContext = ctx->stringExpression();
    if (nullptr != stringContext) return visitStringExpression(stringContext);
    auto identifierContext = ctx->identifierExpression();
    if (nullptr != identifierContext) {
        auto identifierName = identifierContext->getText();
        auto identifierValue = this->emitter->lookupVariable(identifierName);
        if (nullptr == identifierValue) {
            throw hoo::CompilerError("Identifier " + identifierName + " is not found.", identifierContext);
        }
        return identifierValue;
    }
    throw hoo::CompilerError("Invalid expression.", ctx);
}

} // namespace hoo
