

#include "dfa.h"
#include "parse.h"

int create_dfa(struct dfa *dfa, char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list) {
	
	if (parse_fa_states(dfa, state_list) == -1) return -1;
	if (parse_fa_alphabet(dfa, alphabet_list) == -1) return -1;
	if (parse_fa_transitions(dfa, transition_list) == -1) return -1;
	if (parse_fa_start(dfa, start_state) == -1) return -1;
	if (parse_fa_end(dfa, end_state_list) == -1) return -1;
	
	return 0;
	
}