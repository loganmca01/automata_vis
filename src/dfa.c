

#include "dfa.h"
#include "parse.h"

int dfa_iter;
int str_iter;
int str_size;

int create_dfa(struct dfa *dfa, char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list) {
	
	dfa = malloc(1 * sizeof(struct dfa))

	if (parse_fa_states(dfa, state_list) == -1) return -1;
	if (parse_fa_alphabet(dfa, alphabet_list) == -1) return -1;
	if (parse_fa_transitions(dfa, transition_list) == -1) return -1;
	if (parse_fa_start(dfa, start_state) == -1) return -1;
	if (parse_fa_end(dfa, end_state_list) == -1) return -1;
	
	return 0;
	
}

int initialize_sequence(struct dfa *dfa, char *original_input, char *converted_input, char **symbol_mappings) {

	int len = strlen(original_input);
	converted_input = malloc(len * sizeof(char));

	char *input_mask = original_input;
	while (*input_mask != 0) {



	}


}