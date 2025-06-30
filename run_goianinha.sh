#!/bin/bash

# Script para compilar e executar programas Goianinha
# Uso: ./run_goianinha.sh programa.gyn

if [ $# -ne 1 ]; then
    echo "Uso: $0 programa.gyn"
    exit 1
fi

PROGRAM=$1
DIR=$(dirname "$PROGRAM")
BASENAME=$(basename "$PROGRAM" .gyn)
MIPS_FILE="${DIR}/${BASENAME}.s"

echo "=== Compilando $PROGRAM ==="
./goianinha "$PROGRAM"

if [ $? -eq 0 ]; then
    echo ""
    echo "=== Executando código MIPS com SPIM ==="
    echo "Arquivo gerado: $MIPS_FILE"
    echo ""
    
    # Executa o programa com SPIM
    echo "run" | spim -file "$MIPS_FILE"
else
    echo "Erro na compilação!"
    exit 1
fi 