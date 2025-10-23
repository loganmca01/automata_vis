#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dfa.h"
#include "parse.h"

int dfa_iter;
int str_iter;
int str_size;

int create_dfa(struct dfa *dfa, char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list, char *symbol_mappings) {
	
	dfa = malloc(1 * sizeof(struct dfa));
	symbol_mappings = calloc(256, sizeof(char));

	if (parse_fa_states(dfa, state_list) == -1) return -1;
	if (parse_fa_alphabet(dfa, alphabet_list, symbol_mappings) == -1) return -1;
	if (parse_fa_transitions(dfa, transition_list, symbol_mappings) == -1) return -1;
	if (parse_fa_start(dfa, start_state) == -1) return -1;
	if (parse_fa_end(dfa, end_state_list) == -1) return -1;
	
	return 0;
	
}

// NOTE: symbol mappings must be +1 of actual location, 0 must be reserved for characters not in alphabet. In practice this table will only be used here, and shouldn't impact much.
int initialize_dfa_sequence(struct dfa *dfa, char *original_input, char *converted_input, char *symbol_mappings) {

	int len = strlen(original_input);
	converted_input = malloc(len * sizeof(char));

	char *original_mask = original_input;
	char *converted_mask = converted_input;
	while (*original_mask != 0) {

		char current = symbol_mappings[*original_mask];

		if (current == 0) {
			fprintf(stderr, "invalid character in input string\n");
			return -1;
		}

		*converted_mask = current - 1;

		converted_mask++;
		original_mask++;
	}
	*converted_mask = 0;

	return 0;
}