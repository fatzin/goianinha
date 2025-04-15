#include "symtable.h"
#include <sstream>
#include <iostream>

std::string VariableSymbol::toString() const {
    std::stringstream ss;
    ss << "Variable: " << name 
       << ", Type: " << dataTypeToString(dataType)
       << ", Line: " << lineNumber
       << ", Position: " << position;
    return ss.str();
}

std::string ParameterSymbol::toString() const {
    std::stringstream ss;
    ss << "Parameter: " << name 
       << ", Type: " << dataTypeToString(dataType)
       << ", Line: " << lineNumber
       << ", Position: " << position;
    if (function) {
        ss << ", Function: " << function->getName();
    }
    return ss.str();
}

std::string FunctionSymbol::toString() const {
    std::stringstream ss;
    ss << "Function: " << name 
       << ", Return Type: " << dataTypeToString(dataType)
       << ", Line: " << lineNumber
       << ", Param Count: " << paramCount;
    return ss.str();
}

bool SymbolTable::insert(std::shared_ptr<Symbol> symbol) {
    if (!symbol) return false;
    
    const std::string& name = symbol->getName();
    if (contains(name)) {
        return false;
    }
    
    symbols[name] = symbol;
    return true;
}

std::shared_ptr<Symbol> SymbolTable::lookup(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        return it->second;
    }
    return nullptr;
}

bool SymbolTable::contains(const std::string& name) const {
    return symbols.find(name) != symbols.end();
}

std::vector<std::shared_ptr<Symbol>> SymbolTable::getAllSymbols() const {
    std::vector<std::shared_ptr<Symbol>> result;
    for (const auto& pair : symbols) {
        result.push_back(pair.second);
    }
    return result;
}

SymbolTableStack::SymbolTableStack() {
    pushScope();
}

SymbolTableStack::~SymbolTableStack() {
    tables.clear();
}

void SymbolTableStack::pushScope() {
    tables.push_back(std::make_shared<SymbolTable>());
}

void SymbolTableStack::popScope() {
    if (!tables.empty()) {
        tables.pop_back();
    }
}

std::shared_ptr<Symbol> SymbolTableStack::lookup(const std::string& name) const {
    for (auto it = tables.rbegin(); it != tables.rend(); ++it) {
        auto symbol = (*it)->lookup(name);
        if (symbol) {
            return symbol;
        }
    }
    return nullptr;
}

bool SymbolTableStack::insertVariable(const std::string& name, DataType type, int lineNumber, int position) {
    if (tables.empty()) return false;
    
    auto variable = std::make_shared<VariableSymbol>(name, type, lineNumber, position);
    return tables.back()->insert(variable);
}

std::shared_ptr<FunctionSymbol> SymbolTableStack::insertFunction(const std::string& name, DataType returnType, int lineNumber, int paramCount) {
    if (tables.empty()) return nullptr;
    
    auto function = std::make_shared<FunctionSymbol>(name, returnType, lineNumber, paramCount);
    if (tables.back()->insert(function)) {
        return function;
    }
    return nullptr;
}

bool SymbolTableStack::insertParameter(const std::string& name, DataType type, int lineNumber, int position, std::shared_ptr<FunctionSymbol> function) {
    if (tables.empty() || !function) return false;
    
    auto parameter = std::make_shared<ParameterSymbol>(name, type, lineNumber, position, function.get());
    function->addParameter(parameter);
    return tables.back()->insert(parameter);
}

std::shared_ptr<SymbolTable> SymbolTableStack::getCurrentScope() const {
    if (tables.empty()) return nullptr;
    return tables.back();
}

bool SymbolTableStack::isEmpty() const {
    return tables.empty();
}

size_t SymbolTableStack::size() const {
    return tables.size();
}

std::string dataTypeToString(DataType type) {
    switch (type) {
        case DataType::INT: return "int";
        case DataType::CHAR: return "car";
        case DataType::VOID: return "void";
        default: return "unknown";
    }
}

std::string symbolTypeToString(SymbolType type) {
    switch (type) {
        case SymbolType::VARIABLE: return "variable";
        case SymbolType::FUNCTION: return "function";
        case SymbolType::PARAMETER: return "parameter";
        default: return "unknown";
    }
}

DataType stringToDataType(const std::string& typeStr) {
    if (typeStr == "int") return DataType::INT;
    if (typeStr == "car") return DataType::CHAR;
    return DataType::VOID;
}
