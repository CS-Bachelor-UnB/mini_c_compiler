CFLAGS = -O3

compile: src/scanner.l src/parser.y utilities.o symbolTable.o code.o syntaxTree.o functionCall.o
	mkdir -p assets/ bin/
	bison src/parser.y -o src/aux/y.tab.c --defines=include/y.tab.h --report=all --report-file=assets/y.states.out
	flex -o src/aux/lex.yy.c src/scanner.l
	gcc $(CFLAGS) src/aux/lex.yy.c src/aux/y.tab.c obj/utilities.o obj/symbolTable.o obj/syntaxTree.o obj/code.o obj/functionCall.o -o bin/compile -I include/

utilities.o: src/aux/utilities.c
	mkdir -p obj/
	gcc -o obj/$@ $< -c -I include/

symbolTable.o: src/aux/symbolTable.c
	gcc -o obj/$@ $< -c -I include/
	
code.o: src/aux/code.c
	gcc -o obj/$@ $< -c -I include/

syntaxTree.o: src/aux/syntaxTree.c
	gcc -o obj/$@ $< -c -I include/

functionCall.o: src/aux/functionCall.c
	gcc -o obj/$@ $< -c -I include/

scanner.lex:

parser.yacc:

.PHONY: clean
clean:
	rm -rf obj/ assets/ bin/ || true
	rm ./src/aux/lex.yy.c ./src/aux/y.tab.c ./include/y.tab.h || true