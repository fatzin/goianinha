CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: symtable_test

symtable_test: main.cpp symtable.cpp symtable.h
	$(CXX) $(CXXFLAGS) -o symtable_test main.cpp symtable.cpp

clean:
	rm -f symtable_test
