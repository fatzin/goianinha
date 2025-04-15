#include <iostream>
#include <string>

void showHelp() {
    std::cout << "Compilador da Linguagem Goianinha\n";
    std::cout << "Uso:\n";
    std::cout << "  ./symtable/symtable_test        - Testar a tabela de símbolos\n";
    std::cout << "  ./lexer/goianinha <arquivo.gyn>   - Analisar um arquivo fonte\n";
}

int main(int argc, char* argv[]) {
    std::cout << "Compilador da Linguagem Goianinha - Versão 1.0\n";
    std::cout << "Trabalho 1: Tabela de Símbolos e Analisador Léxico\n\n";
    
    showHelp();
    
    return 0;
}