CC = g++
CFLAGS = -std=c++17

all: goianinha

goianinha: lex.yy.c parser/goianinha.tab.c
	$(CC) $(CFLAGS) -o goianinha lex.yy.c parser/goianinha.tab.c

lex.yy.c: goianinha.l
	flex goianinha.l

parser/goianinha.tab.c: parser/goianinha.y
	bison -d -o parser/goianinha.tab.c parser/goianinha.y

clean:
	rm -f goianinha lex.yy.c parser/goianinha.tab.c parser/goianinha.tab.h

test:
	@for file in test_program/*.gyn; do \
		echo "\n--------------file: $$file------------------"; \
		echo "Testando $$file:"; \
		echo "-------------stdout--------------"; \
		./goianinha $$file || true; \
	done

