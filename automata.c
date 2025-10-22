#include <stdio.h>


struct transition_function {
	char *state1;
	char *state2:
	char input_symbol;
};

// better way to do this than separate members for size of arrays?
// better to associate transitions directly with states?
struct dfa {
	char **states;
	int num_states;
	
	char *alphabet;
	int num_symbols;
	
	struct transition_function *transition_set;
	int num_transitions;
	
	char *start;
	char **end;
	int num_ends;
};

int main() {
	
	
	printf("test\n");
	
	
	
	
	
}