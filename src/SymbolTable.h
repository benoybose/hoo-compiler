#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <llvm/IR/Value.h>
#include <vector>
#include <map>

namespace hoo {
struct SymbolTableEntry {
    std::string name;
    llvm::Value* value;
};

class SymbolTable {
public:
    std::vector<std::map<std::string, SymbolTableEntry>> levels;

    void pushScope() {
        levels.push_back({});
    }

    void popScope() {
        levels.pop_back();
    }

    void insertVariable(const std::string& name, llvm::Value* value) {
        levels.back()[name] = {name, value};
    }

    llvm::Value* lookupVariable(const std::string& name) {
        for (auto it = levels.rbegin(); it != levels.rend(); ++it) {
            auto entryIt = it->find(name);
            if (entryIt != it->end()) {
                return entryIt->second.value;
            }
        }
        return nullptr;
    }
};
}
#endif // SYMBOL_TABLE_H
