
#include "./def.h"


struct dfa {
	
	struct state *states;
	char *alphabet;
	
	int num_states;
	int num_symbols;
	
	struct transition_function *transition_set;
	
	/* end state info instead stored directly in state struct */
	struct state *start; // TODO: determine if its faster to include this extra memory here or just go through states to check for start
	//char **end;
	//int num_ends;
	
};

int create_dfa(char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list);

int progress_dfa(struct dfa *dfa, struct state *current, char *input, int input_loc);