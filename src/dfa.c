#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dfa.h"
#include "parse.h"

// TODO: when getting toward nfa and more computational complexity, see if using chars for iters speeds it up at all
unsigned char dfa_iter;
int str_iter;
int str_size;

// memory allocation trackers
int input_alloc = 0;
int dfa_alloc_track = 0;

unsigned char symbol_mappings[256];
struct dfa dfa;

int create_dfa(char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list) {
	
	//*dfa = malloc(1 * sizeof(struct dfa));
	//dfa_alloc = 1;
	
	//*symbol_mappings = malloc(256, sizeof(char));
	memset(&symbol_mappings, 255, 256);
	//symbol_alloc = 1;

	if (parse_fa_states(&dfa, state_list) == -1) {
		free_dfa_mem(NULL);
		return -1;
	}
	if (parse_fa_alphabet(&dfa, alphabet_list, &symbol_mappings[0]) == -1) {
		dfa_alloc_track = 1;
		free_dfa_mem(NULL);
		return -1;
	}
	if (parse_fa_transitions(&dfa, transition_list, &symbol_mappings[0]) == -1) {
		dfa_alloc_track = 2;
		free_dfa_mem(NULL);
		return -1;
	}
	if (parse_fa_start(&dfa, start_state) == -1) {
		dfa_alloc_track = 3;
		free_dfa_mem(NULL);
		return -1;
	}
	if (parse_fa_end(&dfa, end_state_list) == -1) {
		dfa_alloc_track = 4;
		free_dfa_mem(NULL);
		return -1;
	}
	
	dfa_alloc_track = 5;
	return 0;
	
}

int initialize_dfa_sequence(char *original_input, char **converted_input) {

	str_size = strlen(original_input);
	*converted_input = malloc(str_size * sizeof(char));
	input_alloc = 1;

	dfa_iter = dfa.start_state;
	str_iter = 0;

	char *original_mask = original_input;
	char *converted_mask = *converted_input;
	while (*original_mask != 0) {

		unsigned char tmp = symbol_mappings[*original_mask]; 

		if (tmp == 255) {
			fprintf(stderr, "invalid character in input string\n");
			free_dfa_mem(converted_input);
			return -1;
		}

		*converted_mask = tmp;

		converted_mask++;
		original_mask++;
	}
	*converted_mask = 0;

	return 0;
}

/* 
 * -1 = error
 * 0 = success, ongoing sequence
 * 1 = success, completed sequence denied
 * 2 = success, completed sequence accepted
 */
int progress_dfa_sequence(char *input) {
	
	// TODO: logging system, track path DFA took (useful for testing dfa's, 100% necessary for nfa's so might as well implement here too)
	unsigned char current = input[str_iter];
	
	// TODO: unsure if we need to check for validity here, if all went right in parsing it shouldn't be possible to have an invalid state change
	dfa_iter = dfa.transition_set[dfa_iter][current];
	
	str_iter++;
	
	if (str_iter == str_size) {
		if (dfa.states[dfa_iter].is_end == 1) return 2;
		else return 1;
	}
	return 0;
	
}


void free_dfa_mem(char **converted_input) {
	
	if (dfa_alloc_track == 1) {
		free(dfa.states);
	}
	else if (dfa_alloc_track == 2) {
		free(dfa.states);
		free(dfa.alphabet);
	}
	else if (dfa_alloc_track >= 3) {
		free(dfa.states);
		free(dfa.alphabet);
		free(dfa.transition_set);
	}

	if (input_alloc) free(*converted_input);
	
	*converted_input = NULL;
	
	input_alloc = 0;

}
