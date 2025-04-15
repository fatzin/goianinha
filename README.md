# Compilador da Linguagem Goianinha

Este é um compilador didático para a linguagem Goianinha. O compilador implementa uma tabela de símbolos e um analisador léxico para a linguagem.

## Estrutura do Projeto

```
Goianinha/
├── main.cpp                 # Programa principal
├── Makefile                 # Makefile principal
├── lexer/                   # Analisador léxico
│   ├── goianinha.l          # Definição Flex do analisador léxico
│   ├── main.c               # Falso analisador sintático para teste
│   └── Makefile             # Makefile do lexer
├── symtable/                # Tabela de símbolos
│   ├── symtable.h           # Definições da tabela de símbolos
│   ├── symtable.cpp         # Implementação da tabela de símbolos
│   ├── main.cpp             # Programa de teste da tabela
│   └── Makefile             # Makefile da tabela de símbolos
└── test_program/            # Arquivos de teste
    ├── teste.gyn            # Programa de exemplo
    ├── fatorialCorreto.gyn  # Cálculo de fatorial funcionando
    └── [outros arquivos]    # Exemplos com erros para testar
```

## Requisitos

- Linux
- GCC/G++ (com suporte a C++17)
- Flex (para gerar o analisador léxico)
- Make

## Compilação

Para compilar o projeto completo:

```bash
cd /caminho/para/Goianinha
make
```

Este comando compilará:

1. O programa principal (`goianinha`)
2. O programa de teste da tabela de símbolos (`symtable/symtable_test`)
3. O analisador léxico (`lexer/goianinha`)

## Como Utilizar

### Testando a Tabela de Símbolos

A tabela de símbolos pode ser testada com o programa de teste incluído:

```bash
./symtable/symtable_test
```

Este comando executará uma série de operações para testar a tabela de símbolos, incluindo:

- Inserção de símbolos em diferentes escopos
- Busca de símbolos através de escopos aninhados
- Criação e remoção de escopos
- Teste de parâmetros de função

### Executando o Analisador Léxico

O analisador léxico pode ser usado para analisar um arquivo fonte da linguagem Goianinha:

```bash
./lexer/goianinha test_program/arquivo.gyn
```

Onde `arquivo.gyn` é o nome do arquivo que você deseja analisar. O analisador imprimirá uma lista de tokens reconhecidos, incluindo:

- TOKEN: Tipo do token (ID, INT, PROGRAMA, etc.)
- LEXEMA: O texto do token no arquivo fonte
- LINHA: Número da linha onde o token foi encontrado

### Verificando Erros

O analisador léxico reporta os seguintes tipos de erros:

- Caracteres inválidos
- Strings não fechadas
- Strings com quebras de linha
- Comentários não fechados

## Arquivos de Teste

O diretório `test_program/` contém exemplos para testar o compilador:

- `fatorialCorreto.gyn`: Um programa correto que calcula o fatorial
- `fatorialErroLin1ComentarioNtermina.gyn`: Erro de comentário não terminado
- `fatorialErroLin15String2linhas.gyn`: Erro de string com quebra de linha
- `expressao1ErroLin4CadeiaNaoTermina.gyn`: Erro de string não terminada
- `erroLin6Caractereinvalido.gyn`: Erro de caractere inválido

## Limpeza

Para limpar os arquivos gerados:

```bash
make clean
```
