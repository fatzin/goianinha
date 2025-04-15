all: main symtable lexer

main:
		g++ -std=c++17 -Wall -Wextra -o goianinha main.cpp

symtable:
		$(MAKE) -C symtable

lexer:
		$(MAKE) -C lexer

clean:
		rm -f goianinha
		$(MAKE) -C symtable clean
		$(MAKE) -C lexer clean

