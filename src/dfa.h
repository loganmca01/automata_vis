
#include "./def.h"


struct dfa {
	
	struct state *states;
	char *alphabet;
	
	int num_states;
	int num_symbols;
	
	struct transition_function *transition_set;
	
	/* end state info instead stored directly in state struct */
	//struct state *start; // TODO: determine if its faster to include this extra memory here or just go through states to check for start
	//char **end;
	//int num_ends;
	
};

/* TODO: decide whether a lot of these are gonna be globals or if we're gonna pass everytthing around */
int create_dfa(struct dfa *dfa, char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list);

int initialize_sequence(struct dfa *dfa, char *original_input, char *converted_input, char **symbol_mappings, int *dfa_iter, int *str_iter);

int progress_sequence(struct dfa *dfa, int *dfa_iter, int *str_iter, char *input);
