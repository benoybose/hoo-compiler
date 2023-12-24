#include <gtest/gtest.h>
#include "antlr/HooVisitor.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"

namespace {

// Mock HooParser::LiteralExpressionContext for testing
class MockLiteralExpressionContext : public HooParser::LiteralExpressionContext {
public:
    MockLiteralExpressionContext(const std::string& text) : text(text) {}
    const std::string& getText() const { return text; }

private:
    std::string text;
};

} // namespace

TEST(HooVisitorTest, VisitLiteralExpression) {
    llvm::LLVMContext context;
    llvm::Module module("test_module", context);
    HooVisitor visitor(context, module);

    // Byte literal test
    {
        MockLiteralExpressionContext byteLiteralContext("0x1A");
        auto value = visitor.visitLiteralExpression(&byteLiteralContext);
        ASSERT_TRUE(llvm::isa<llvm::ConstantInt>(value));
        EXPECT_EQ(value->getValue().getZExtValue(), 0x1A);
    }

    // Char literal test
    {
        MockLiteralExpressionContext charLiteralContext("'a'");
        auto value = visitor.visitLiteralExpression(&charLiteralContext);
        ASSERT_TRUE(llvm::isa<llvm::GlobalVariable>(value));
        // Use appropriate assertions to verify the character value
    }

    // Boolean literal test
    {
        MockLiteralExpressionContext booleanLiteralContext("true");
        auto value = visitor.visitLiteralExpression(&booleanLiteralContext);
        ASSERT_TRUE(llvm::isa<llvm::ConstantInt>(value));
        EXPECT_EQ(value->getValue().getZExtValue(), 1); // True value
    }

    // Integer literal test
    {
        MockLiteralExpressionContext integerLiteralContext("42");
        auto value = visitor.visitLiteralExpression(&integerLiteralContext);
        ASSERT_TRUE(llvm::isa<llvm::ConstantInt>(value));
        EXPECT_EQ(value->getValue().getSExtValue(), 42);
    }

    // Double literal test
    {
        MockLiteralExpressionContext doubleLiteralContext("3.14159");
        auto value = visitor.visitLiteralExpression(&doubleLiteralContext);
        ASSERT_TRUE(llvm::isa<llvm::ConstantFP>(value));
        EXPECT_DOUBLE_EQ(value->getValueAPF().convertToDouble(), 3.14159);
    }
}
