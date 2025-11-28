all: automata.o dfa.o nfa.o dpda.o npda.o parse.o
	cc -o automata automata.o dfa.o nfa.o dpda.o npda.o parse.o
	
automata.o: src/automata.c
	cc -o automata.o -c src/automata.c
	
dfa.o: src/dfa.c
	cc -o dfa.o -c src/dfa.c
	
nfa.o: src/nfa.c
	cc -o nfa.o -c src/nfa.c
	
dpda.o: src/dpda.c
	cc -o dpda.o -c src/dpda.c
	
npda.o: src/npda.c
	cc -o npda.o -c src/npda.c
	
parse.o: src/parse.c
	cc -o parse.o -c src/parse.c
	
test: test.c
	cc -g -gdwarf-4 -o test test.c
	
wasm: ./src/automata.c ./src/dfa.c ./src/nfa.c ./src/dpda.c ./src/npda.c ./src/parse.c
	emcc -o ./frontend/automata.html ./src/automata.c ./src/dfa.c ./src/nfa.c ./src/dpda.c ./src/npda.c ./src/parse.c \
	--preload-file test_automata