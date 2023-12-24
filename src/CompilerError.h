#include <stdexcept>
#include "antlr/HooParser.h"

namespace hoo {
class CompilerError : public std::runtime_error {
public:
    CompilerError(const std::string& message, const antlr4::ParserRuleContext* ctx)
            : std::runtime_error(message), line(ctx->start->getLine()), charPosition(ctx->start->getCharPositionInLine()) {}

    unsigned int getLine() const { return line; }
    unsigned int getCharPosition() const { return charPosition; }

private:
    unsigned int line;
    unsigned int charPosition;
};
}
