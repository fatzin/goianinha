#include "symtable.h"
#include <iostream>

void printSymbol(std::shared_ptr<Symbol> symbol) {
    if (symbol) {
        std::cout << symbol->toString() << std::endl;
    } else {
        std::cout << "Símbolo não encontrado!" << std::endl;
    }
}

int main() {
    std::cout << "=== Teste da Tabela de Símbolos ===" << std::endl;
    
    SymbolTableStack symbolStack;
    
    std::cout << "\n== Testando escopo global ==" << std::endl;
    
    symbolStack.insertVariable("x", DataType::INT, 1, 0);
    symbolStack.insertVariable("y", DataType::CHAR, 2, 1);
    auto mainFunc = symbolStack.insertFunction("main", DataType::INT, 3, 0);
    
    std::cout << "Procurando 'x': ";
    printSymbol(symbolStack.lookup("x"));
    
    std::cout << "Procurando 'main': ";
    printSymbol(symbolStack.lookup("main"));
    
    symbolStack.pushScope();
    std::cout << "\n== Testando escopo local ==" << std::endl;
    
    symbolStack.insertVariable("i", DataType::INT, 4, 0);
    symbolStack.insertVariable("c", DataType::CHAR, 5, 1);

    symbolStack.insertVariable("x", DataType::INT, 6, 2);
    
    std::cout << "Procurando 'i': ";
    printSymbol(symbolStack.lookup("i"));
    
    std::cout << "Procurando 'x' (deve ser o local): ";
    printSymbol(symbolStack.lookup("x"));
    
    std::cout << "Procurando 'y' (do escopo global): ";
    printSymbol(symbolStack.lookup("y"));
    
    symbolStack.pushScope();
    std::cout << "\n== Testando escopo aninhado ==" << std::endl;
    
    symbolStack.insertVariable("j", DataType::INT, 7, 0);
    
    std::cout << "Procurando 'j': ";
    printSymbol(symbolStack.lookup("j"));
    
    std::cout << "Procurando 'i' (do escopo pai): ";
    printSymbol(symbolStack.lookup("i"));
    
    symbolStack.popScope();
    std::cout << "\n== Depois de remover o escopo aninhado ==" << std::endl;
    
    std::cout << "Procurando 'j' (não deveria existir): ";
    printSymbol(symbolStack.lookup("j"));
    
    std::cout << "Procurando 'i' (ainda acessível): ";
    printSymbol(symbolStack.lookup("i"));
    
    std::cout << "\n== Testando função com parâmetros ==" << std::endl;
    
    auto funcWithParams = symbolStack.insertFunction("calculate", DataType::INT, 10);
    
    symbolStack.insertParameter("a", DataType::INT, 10, 0, funcWithParams);
    symbolStack.insertParameter("b", DataType::INT, 10, 1, funcWithParams);
    
    std::cout << "Função: " << funcWithParams->toString() << std::endl;
    std::cout << "Quantidade de parâmetros: " << funcWithParams->getParamCount() << std::endl;
    
    std::cout << "\n== Limpando recursos ==" << std::endl;
    symbolStack.popScope();
    
    std::cout << "Escopos restantes: " << symbolStack.size() << std::endl;
    std::cout << "Teste concluído com sucesso!" << std::endl;
    
    return 0;
}
