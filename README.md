# Compilador Goianinha - Implementação Completa

Este projeto implementa um compilador completo para a linguagem Goianinha, desenvolvido como parte da disciplina de Compiladores. O compilador converte código fonte Goianinha em assembly MIPS executável.

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

### ✅ Fase 4: Geração de Código MIPS (Parte 3)

- **Arquivos**: `codegen/codegen.h`, `codegen/codegen.c`
- **Funcionalidades Básicas**:

  - Geração de código assembly MIPS funcional
  - Seção `.data` para variáveis globais
  - Seção `.text` com código executável
  - Operações aritméticas básicas (+, -, \*, /)
  - Comandos de entrada/saída (`leia`, `escreva`)
  - Estruturas de controle (if, while)
  - Atribuições simples

- **Funcionalidades Avançadas**:
  - **Suporte a múltiplos parâmetros**: Até 4 parâmetros usando registradores $a0-$a3
  - **Gestão inteligente de pilha**: Sistema dinâmico de salvamento de registradores
  - **Recursão robusta**: Suporte completo para funções recursivas complexas
  - **Resolução de escopo**: Precedência correta entre parâmetros e variáveis globais
  - **Otimização de registradores**: Salvamento seletivo baseado no contexto
  - **Sistema de labels únicos**: Para strings e estruturas de controle

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
│   ├── teste_fibonacci.gyn     # Teste de recursão
│   ├── teste_4_params.gyn      # Teste de múltiplos parâmetros
│   ├── teste_aninhado.gyn      # Estruturas aninhadas
│   ├── teste_escopo.gyn        # Resolução de escopo
│   ├── teste_expressoes.gyn    # Expressões complexas
│   ├── teste_hanoi.gyn         # Torre de Hanoi
│   └── teste_simples_final.gyn # Teste síntese
├── run_goianinha.sh     # Script de execução
├── Makefile            # Compilação do projeto
└── README.md           # Este arquivo
```

## Como Usar

### Compilação

```bash
make clean && make
```

### Execução Básica

```bash
./goianinha programa.gyn
```

O compilador irá:

1. Realizar análise léxica e sintática
2. Construir e exibir a AST
3. Executar análise semântica
4. Gerar código MIPS no arquivo `programa.s`

### Execução com Script

Para facilidade de uso:

```bash
./run_goianinha.sh programa.gyn
```

Este script:

- Compila o programa Goianinha
- Gera o arquivo `.s`

### Execução no MARS

O código também é compatível com o simulador MARS:

1. Abra o MARS
2. Carregue o arquivo `.s` gerado
3. Execute o programa

## Testes Disponíveis

O projeto inclui uma bateria completa de testes para validar todas as funcionalidades:

| Teste                     | Funcionalidade          | Complexidade  |
| ------------------------- | ----------------------- | ------------- |
| `teste_simples_final.gyn` | Funcionalidades básicas | Básica        |
| `teste_expressoes.gyn`    | Expressões matemáticas  | Intermediária |
| `teste_4_params.gyn`      | Múltiplos parâmetros    | Intermediária |
| `teste_aninhado.gyn`      | Estruturas aninhadas    | Avançada      |
| `teste_escopo.gyn`        | Resolução de escopo     | Avançada      |
| `teste_fibonacci.gyn`     | Recursão simples        | Avançada      |
| `teste_hanoi.gyn`         | Recursão complexa       | Extrema       |

### Executar Todos os Testes

```bash
# Executar teste específico
./run_goianinha.sh test_program/teste_fibonacci.gyn

# Para testar múltiplos arquivos
for teste in test_program/teste_*.gyn; do
    echo "Testando: $teste"
    ./run_goianinha.sh "$teste"
done
```

## Exemplos de Código

### Programa Simples

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

### Fibonacci Recursivo

```goianinha
int n, resultado;

int fibonacci(int num) {
    se (num <= 1) entao {
        retorne num;
    } senao {
        retorne fibonacci(num - 1) + fibonacci(num - 2);
    }
}

programa {
    leia n;
    resultado = fibonacci(n);
    escreva resultado;
    novalinha;
}
```

### Múltiplos Parâmetros

```goianinha
int a, b, c, d, resultado;

int calcula(int x, int y, int z, int w) {
    retorne (x + y) * (z - w);
}

programa {
    leia a;
    leia b;
    leia c;
    leia d;
    resultado = calcula(a, b, c, d);
    escreva resultado;
    novalinha;
}
```

## Características da Linguagem

- **Tipos de dados**: `int` (inteiro) e `car` (caractere)
- **Declarações**: Variáveis globais e locais, funções com até 4 parâmetros
- **Comandos**:
  - `leia` - entrada de dados
  - `escreva` - saída de dados
  - `novalinha` - quebra de linha
  - `se...entao...senao` - condicional (palavra `entao` obrigatória)
  - `enquanto...execute` - laço
  - `retorne` - retorno de função
- **Expressões**: Aritméticas (+, -, \*, /), relacionais, chamadas de função
- **Operadores**: +, -, \*, /, ==, !=, <, >, <=, >=, =

## Regras Semânticas Implementadas

1. **Escopo**: Funções devem ser declaradas antes do bloco principal
2. **Tipos**: Verificação de compatibilidade em operações e atribuições
3. **Declarações**: Variáveis devem ser declaradas antes do uso
4. **Funções**: Verificação de parâmetros e tipo de retorno
5. **Comandos**: `retorne` apenas em funções, condicionais com tipos corretos
6. **Precedência**: Parâmetros têm precedência sobre variáveis globais no escopo local

## Arquitetura MIPS Gerada

### Segmento de Dados

```mips
.data
    # Variáveis globais
    var_name: .word 0
    string_labels: .asciiz "..."
```

### Segmento de Código

```mips
.text
.globl main

# Funções com prólogo/epílogo
function_name:
    # Prólogo: salvamento de contexto
    addi $sp, $sp, -16
    sw $ra, 12($sp)

    # Corpo da função
    # ...

    # Epílogo: restauração de contexto
    lw $ra, 12($sp)
    addi $sp, $sp, 16
    jr $ra

# Programa principal
main:
    # Inicialização da pilha
    la $sp, 0x7ffe0000
    # Código do programa
    # ...
    # Finalização
    li $v0, 10
    syscall
```

## Características Técnicas Avançadas

### Gestão de Registradores

- **$t0-$t9**: Registradores temporários para expressões
- **$a0-$a3**: Parâmetros de função (até 4 parâmetros)
- **$v0-$v1**: Valores de retorno e syscalls
- **$sp**: Stack pointer com 128KB de espaço

### Sistema de Pilha Inteligente

- **Salvamento seletivo**: Registradores salvos apenas quando necessário
- **Offset dinâmico**: Cálculo automático de posições na pilha
- **Detecção de contexto**: Análise automática de múltiplas chamadas

### Otimizações Implementadas

- **Prevenção de stack overflow**: Alocação adequada de memória
- **Preservação inteligente**: Salvamento baseado no padrão de uso
- **Labels únicos**: Sistema de numeração para evitar conflitos

## Status do Projeto

✅ **COMPLETO** - Todas as 4 fases implementadas e funcionais:

- ✅ Análise léxica
- ✅ Análise sintática com AST
- ✅ Análise semântica com verificações completas
- ✅ Geração de código MIPS otimizada

## Autores

Projeto desenvolvido para a disciplina de Compiladores.

## Licença

Este projeto é desenvolvido para fins acadêmicos.
