
#include "./def.h"

struct dfa {
	
	struct state *states;
	int num_states;
	
	char *alphabet;
	int num_symbols;
	
	struct transition_function *transition_set;
	
	char *start;
	char **end;
	int num_ends;
	
};

int create_dfa(char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list);