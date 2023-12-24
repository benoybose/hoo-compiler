#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <memory>

#include "antlr/HooBaseVisitor.h"
#include "Emitter.h"

namespace hoo {
class HooVisitor: public HooBaseVisitor {
public:
    enum LiteralType {
        IntegerLiteral,
        CharLiteral,
        StringLiteral,
        BooleanLiteral,
        ByteLiteral,
        DoubleLiteral
    };

public:
    HooVisitor(llvm::LLVMContext& context, llvm::Module& module);

public:
    antlrcpp::Any visitLiteralExpression(HooParser::LiteralExpressionContext *ctx) override;
    antlrcpp::Any visitStringExpression(HooParser::StringExpressionContext *ctx) override;
    antlrcpp::Any visitPrimaryExpression(HooParser::PrimaryExpressionContext *ctx) override;
    antlrcpp::Any visitCastExpression(HooParser::CastExpressionContext *ctx) override;

private:
    static LiteralType determineLiteralType(HooParser::LiteralExpressionContext* context) {
        if (context->ByteLiteral()) {
        return ByteLiteral;
        } else if (context->IntegerLiteral()) {
        return IntegerLiteral;
        } else if (context->DoubleLiteral()) {
        return DoubleLiteral;
        } else if (context->CharLiteral()) {
            return CharLiteral;
        } else if (context->BooleanLiteral()) {
            return BooleanLiteral;
        }
        throw std::runtime_error("Unrecognized literal type");
    }

private:
    llvm::LLVMContext& context; 
    llvm::Module& module;
    std::unique_ptr<hoo::Emitter> emitter;
};

}
