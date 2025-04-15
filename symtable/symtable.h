#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Enumeração para os tipos de dados suportados
enum class DataType {
    INT,
    CHAR,
    VOID
};

// Enumeração para os tipos de símbolos
enum class SymbolType {
    VARIABLE,
    FUNCTION,
    PARAMETER
};

// Declaração antecipada para referência circular
class FunctionSymbol;

// Classe base para todos os símbolos
class Symbol {
protected:
    std::string name;
    DataType dataType;
    SymbolType symbolType;
    int lineNumber;

public:
    Symbol(const std::string& name, DataType dataType, SymbolType symbolType, int lineNumber)
        : name(name), dataType(dataType), symbolType(symbolType), lineNumber(lineNumber) {}
    
    virtual ~Symbol() = default;
    
    std::string getName() const { return name; }
    DataType getDataType() const { return dataType; }
    SymbolType getSymbolType() const { return symbolType; }
    int getLineNumber() const { return lineNumber; }
    
    virtual std::string toString() const = 0;
};

// Símbolo para variáveis
class VariableSymbol : public Symbol {
private:
    int position; // Posição na declaração

public:
    VariableSymbol(const std::string& name, DataType dataType, int lineNumber, int position)
        : Symbol(name, dataType, SymbolType::VARIABLE, lineNumber), position(position) {}
    
    int getPosition() const { return position; }
    
    std::string toString() const override;
};

// Símbolo para parâmetros de função
class ParameterSymbol : public Symbol {
private:
    int position; // Posição na lista de parâmetros
    FunctionSymbol* function; // Função à qual o parâmetro pertence

public:
    ParameterSymbol(const std::string& name, DataType dataType, int lineNumber, int position, FunctionSymbol* function)
        : Symbol(name, dataType, SymbolType::PARAMETER, lineNumber), position(position), function(function) {}
    
    int getPosition() const { return position; }
    FunctionSymbol* getFunction() const { return function; }
    
    std::string toString() const override;
};

// Símbolo para funções
class FunctionSymbol : public Symbol {
private:
    int paramCount;
    std::vector<std::shared_ptr<ParameterSymbol>> parameters;

public:
    FunctionSymbol(const std::string& name, DataType returnType, int lineNumber, int paramCount = 0)
        : Symbol(name, returnType, SymbolType::FUNCTION, lineNumber), paramCount(paramCount) {}
    
    int getParamCount() const { return paramCount; }
    
    void addParameter(std::shared_ptr<ParameterSymbol> param) {
        parameters.push_back(param);
        paramCount = parameters.size();
    }
    
    std::vector<std::shared_ptr<ParameterSymbol>> getParameters() const { return parameters; }
    
    std::string toString() const override;
};

// Classe para um escopo na tabela de símbolos
class SymbolTable {
private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;

public:
    SymbolTable() = default;

    // Inserir um símbolo na tabela
    bool insert(std::shared_ptr<Symbol> symbol);
    
    // Procurar um símbolo pelo nome
    std::shared_ptr<Symbol> lookup(const std::string& name) const;
    
    // Verifica se um símbolo existe na tabela
    bool contains(const std::string& name) const;
    
    // Retorna todos os símbolos na tabela
    std::vector<std::shared_ptr<Symbol>> getAllSymbols() const;
};

// Classe para gerenciar a pilha de tabelas de símbolos
class SymbolTableStack {
private:
    std::vector<std::shared_ptr<SymbolTable>> tables;

public:
    // Inicializar a pilha de tabelas de símbolos
    SymbolTableStack();
    
    // Destruir a pilha de tabelas de símbolos
    ~SymbolTableStack();
    
    // Criar e empilhar um novo escopo
    void pushScope();
    
    // Remover o escopo atual
    void popScope();
    
    // Pesquisar um nome na pilha (do topo à base)
    std::shared_ptr<Symbol> lookup(const std::string& name) const;
    
    // Inserir um nome de variável no escopo atual
    bool insertVariable(const std::string& name, DataType type, int lineNumber, int position);
    
    // Inserir um nome de função no escopo atual
    std::shared_ptr<FunctionSymbol> insertFunction(const std::string& name, DataType returnType, int lineNumber, int paramCount = 0);
    
    // Inserir um nome de parâmetro no escopo atual
    bool insertParameter(const std::string& name, DataType type, int lineNumber, int position, std::shared_ptr<FunctionSymbol> function);
    
    // Obtém o escopo atual
    std::shared_ptr<SymbolTable> getCurrentScope() const;
    
    // Verificar se a pilha está vazia
    bool isEmpty() const;
    
    // Obter o tamanho da pilha
    size_t size() const;
};

// Funções auxiliares para conversão de tipos
std::string dataTypeToString(DataType type);
std::string symbolTypeToString(SymbolType type);
DataType stringToDataType(const std::string& typeStr);

#endif // SYMTABLE_H