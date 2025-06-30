CC = g++
CFLAGS = -std=c++17

all: goianinha

goianinha: lex.yy.c parser/goianinha.tab.c parser/ast.c symtable/symtable.c semantic/semantic.c codegen/codegen.c
	$(CC) $(CFLAGS) -o goianinha lex.yy.c parser/goianinha.tab.c parser/ast.c symtable/symtable.c semantic/semantic.c codegen/codegen.c

lex.yy.c: goianinha.l
	flex goianinha.l

parser/goianinha.tab.c: parser/goianinha.y parser/ast.h symtable/symtable.h semantic/semantic.h codegen/codegen.h
	bison -d -o parser/goianinha.tab.c parser/goianinha.y

clean:
	rm -f goianinha lex.yy.c parser/goianinha.tab.c parser/goianinha.tab.h *.s

test:
	@for file in test_program/*.gyn; do \
		echo "\n--------------file: $$file------------------"; \
		echo "Testando $$file:"; \
		echo "-------------stdout--------------"; \
		./goianinha $$file || true; \
	done

