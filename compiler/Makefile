MKDIR_P = mkdir -p
BINDIR = /bin

.PHONY: create_bin_dir

all: linux

linux : create clear yacc lex compileLinux
mac : create clear yacc lex compileMac

create:
	mkdir -p bin
	rm -f test/codegen.s && touch test/codegen.s

clear : 
	clear

yacc : 
	bison -d src/compiler.y -o compiler.cc
	mv compiler.cc src/
	mv compiler.hh src/

lex : 
	flex src/compiler.l 
	mv lex.yy.c src/

compileLinux : 
	echo "Compiling for Linux"
	g++ -g -std=c++17 src/lex.yy.c src/compiler.cc src/functions.cpp src/codegen.cpp -I src/functions.h -I include/compiler.h -o bin/compiler

compileMac : 
	echo "Compiling for Mac"
	clang++ -g -std=c++17 src/lex.yy.c src/compiler.cc src/functions.cpp src/codegen.cpp -I src/functions.h -I include/compiler.h -o bin/compiler

run : clear execute

mdebug: clear macDebugger
ldebug: clear linuxDebugger

macDebugger : 
	gdb ./bin/compiler 

linuxDebugger : 
	lldb ./bin/compiler 

execute:
	./bin/compiler < test/input.sil > test/output.txt

clean : 
	rm src/compiler.hh src/compiler.cc bin/compiler src/lex.yy.c 
	rm -rf bin/compiler.dSYM
	rm -rf bin
	rm -rf test/codegen.s
