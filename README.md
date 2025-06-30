# Compilador Goianinha - Implementação Completa

Este projeto implementa um compilador completo para a linguagem Goianinha, desenvolvido como parte da disciplina de Compiladores.

## Fases Implementadas

### ✅ Fase 1: Análise Léxica

- **Arquivo**: `goianinha.l` (Flex)
- **Funcionalidades**:
  - Reconhecimento de tokens (palavras-chave, identificadores, operadores, constantes)
  - Tratamento de comentários e espaços em branco
  - Detecção de erros léxicos
  - Suporte para tipos `int` e `car`

### ✅ Fase 2: Análise Sintática e AST

- **Arquivos**: `parser/goianinha.y` (Bison), `parser/ast.h`, `parser/ast.c`
- **Funcionalidades**:
  - Parser completo para a gramática da linguagem Goianinha
  - Construção da Árvore Sintática Abstrata (AST)
  - Detecção de erros sintáticos
  - Suporte para:
    - Declarações de variáveis e funções
    - Comandos (se, enquanto, leia, escreva)
    - Expressões aritméticas e chamadas de função

### ✅ Fase 3: Análise Semântica

- **Arquivos**: `semantic/semantic.h`, `semantic/semantic.c`, `symtable/symtable.h`, `symtable/symtable.c`
- **Funcionalidades**:
  - Tabela de símbolos hierárquica para gerenciamento de escopos
  - Verificações semânticas:
    - Declaração antes do uso
    - Compatibilidade de tipos
    - Verificação de parâmetros em chamadas de função
    - Comando `retorne` apenas em funções
    - Tipos corretos em condicionais

### ✅ Fase 4: Geração de Código MIPS

- **Arquivos**: `codegen/codegen.h`, `codegen/codegen.c`
- **Funcionalidades**:
  - Geração de código assembly MIPS funcional
  - Suporte para:
    - Variáveis globais na seção `.data`
    - Operações aritméticas básicas (+, -, \*, /)
    - Comandos de entrada/saída (`leia`, `escreva`)
    - Funções com prólogo/epílogo
    - Estruturas de controle (if, while)
    - Atribuições e chamadas de função

## Estrutura do Projeto

```
.
├── goianinha.l           # Analisador léxico (Flex)
├── parser/
│   ├── goianinha.y       # Analisador sintático (Bison)
│   ├── ast.h            # Definições da AST
│   └── ast.c            # Implementação da AST
├── symtable/
│   ├── symtable.h       # Tabela de símbolos
│   └── symtable.c       # Implementação da tabela
├── semantic/
│   ├── semantic.h       # Analisador semântico
│   └── semantic.c       # Implementação da análise semântica
├── codegen/
│   ├── codegen.h        # Gerador de código MIPS
│   └── codegen.c        # Implementação do gerador
├── test_program/        # Programas de teste
├── main.cpp             # Programa principal (não usado)
├── Makefile            # Compilação do projeto
└── README.md           # Este arquivo
```

## Como Usar

### Compilação

```bash
make clean && make
```

### Execução

```bash
./goianinha programa.gyn
```

O compilador irá:

1. Realizar análise léxica e sintática
2. Construir e exibir a AST
3. Executar análise semântica
4. Gerar código MIPS no arquivo `programa.s`

### Exemplo de Programa Goianinha

```goianinha
int x, y, resultado;

int soma(int a, int b) {
    retorne a + b;
}

programa {
    leia x;
    leia y;
    resultado = soma(x, y);
    escreva resultado;
    novalinha;
}
```

### Código MIPS Gerado

O compilador gera código MIPS assembly válido que pode ser executado em simuladores como MARS ou SPIM.

## Características da Linguagem

- **Tipos de dados**: `int` (inteiro) e `car` (caractere)
- **Declarações**: Variáveis globais e locais, funções
- **Comandos**:
  - `leia` - entrada de dados
  - `escreva` - saída de dados
  - `novalinha` - quebra de linha
  - `se...senao` - condicional
  - `enquanto` - laço
  - `retorne` - retorno de função
- **Expressões**: Aritméticas (+, -, \*, /), relacionais, chamadas de função
- **Operadores**: +, -, \*, /, ==, !=, <, >, <=, >=, =

## Regras Semânticas Implementadas

1. **Escopo**: Funções devem ser declaradas antes do bloco principal
2. **Tipos**: Verificação de compatibilidade em operações e atribuições
3. **Declarações**: Variáveis devem ser declaradas antes do uso
4. **Funções**: Verificação de parâmetros e tipo de retorno
5. **Comandos**: `retorne` apenas em funções, condicionais com tipos corretos

## Status do Projeto

✅ **COMPLETO** - Todas as 4 fases implementadas e funcionais:

- Análise léxica
- Análise sintática com AST
- Análise semântica com verificações
- Geração de código MIPS

O compilador está pronto para apresentação e uso!
