CC = gcc
CFLAGS = -Wall -Wextra

all: goianinha

# Gerar código-fonte C a partir da especificação Flex
lex.yy.c: goianinha.l
	flex goianinha.l

# Compilar o analisador léxico com o programa principal
goianinha: lex.yy.c main.c
	$(CC) $(CFLAGS) -o goianinha lex.yy.c main.c

clean:
	rm -f goianinha lex.yy.c
