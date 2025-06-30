#!/bin/bash

echo "=== TESTE DE EXECUÇÃO DO COMPILADOR GOIANINHA ==="
echo ""

# Compilar o programa de teste
echo "1. Compilando programa teste_spim.gyn..."
./goianinha test_program/teste_spim.gyn > /dev/null 2>&1

if [ $? -eq 0 ]; then
    echo "✅ Compilação bem-sucedida!"
    echo ""
    echo "2. Código MIPS gerado:"
    echo "----------------------------------------"
    cat test_program/teste_spim.s
    echo "----------------------------------------"
    echo ""
    echo "3. Para executar no SPIM:"
    echo "   spim -file test_program/teste_spim.s"
    echo "   (No prompt do SPIM, digite: run)"
    echo ""
    echo "4. Programa compilado com sucesso!"
    echo "   Este programa deve imprimir: 42"
else
    echo "❌ Erro na compilação!"
fi 