#include "def.h"
#include "dfa.h"

#ifndef PARSE
#define PARSE

/*
    Take in inputs in format q1,a,q2;q1,b,q3
*/

int parse_fa_states(struct dfa *dfa , char *state_list);
int parse_fa_alphabet(struct dfa *dfa , char *alphabet_list, unsigned char *symbol_mappings);
int parse_fa_transitions(struct dfa *dfa , char *transition_list, unsigned char *symbol_mappings);
int parse_fa_start(struct dfa *dfa , char *start_state);
int parse_fa_end(struct dfa *dfa , char *end_state_list);


#endif /* PARSE */