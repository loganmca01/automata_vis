#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dfa.h"
#include "parse.h"

int dfa_iter;
int str_iter;
int str_size;

// booleans
int complete = 0;
int dfa_alloc = 0;
int symbol_alloc = 0;
int input_alloc = 0;

//TODO MAYBE: trackers for if memory is allocated to different things so it doesn't break trying to free something that wasn't
// allocated on an error

// TODO: decide if it's better to just exit on errors in these outermost functions or return -1 and exit in main
int create_dfa(struct dfa *dfa, char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list, char *symbol_mappings) {
	
	dfa = malloc(1 * sizeof(struct dfa));
	dfa_alloc = 1;
	
	symbol_mappings = calloc(256, sizeof(char));
	symbol_alloc = 1;

	if (parse_fa_states(dfa, state_list) == -1) {
		free_dfa_mem(dfa, symbol_mappings, NULL);
		return -1;
	}
	if (parse_fa_alphabet(dfa, alphabet_list, symbol_mappings) == -1) {
		free_dfa_mem(dfa, symbol_mappings, NULL);
		return -1;
	}
	if (parse_fa_transitions(dfa, transition_list, symbol_mappings) == -1) {
		free_dfa_mem(dfa, symbol_mappings, NULL);
		return -1;
	}
	if (parse_fa_start(dfa, start_state) == -1) {
		free_dfa_mem(dfa, symbol_mappings, NULL);
		return -1;
	}
	if (parse_fa_end(dfa, end_state_list) == -1) {
		free_dfa_mem(dfa, symbol_mappings, NULL);
		return -1;
	}
	
	return 0;
	
}

// NOTE: symbol mappings must be +1 of actual location, 0 must be reserved for characters not in alphabet. In practice this table will
// only be used here, and shouldn't impact much.
int initialize_dfa_sequence(struct dfa *dfa, char *original_input, char *converted_input, char *symbol_mappings) {

	str_size = strlen(original_input);
	converted_input = malloc(str_size * sizeof(char));
	input_alloc = 1;

	dfa_iter = dfa->start_state;
	str_iter = 0;

	char *original_mask = original_input;
	char *converted_mask = converted_input;
	while (*original_mask != 0) {

		char current = symbol_mappings[*original_mask]; 

		if (current == 0) {
			fprintf(stderr, "invalid character in input string\n");
			free_dfa_mem(dfa, symbol_mappings, converted_input);
			return -1;
		}

		*converted_mask = current - 1;

		converted_mask++;
		original_mask++;
	}
	*converted_mask = 0;

	return 0;
}

/* TODO: better system for returns here
 * -1 = error
 * 0 = success, ongoing sequence
 * 1 = success, completed sequence denied
 * 2 = success, completed sequence accepted
*/
int progress_dfa_sequence(struct dfa *dfa, char *input) {
	
	char current = input[str_iter];
	
	
	
}


void free_dfa_mem(struct dfa *dfa, char *symbol_mappings, char *converted_input) {
	
	if (dfa_alloc) free(dfa);
	if (symbol_alloc) free(symbol_mappings);
	if (input_alloc) free(converted_input);
	
	dfa_alloc = 0;
	symbol_alloc = 0;
	input_alloc = 0;

}
