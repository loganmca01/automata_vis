#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //reminder to figure out if here or header or not needed becuase it's in main

int parse_fa_states(struct dfa *dfa, char *state_list) {
    char *copy = strdup(state_list);
    //add check if copy fails?

    int count = 1; //starts at one becuase state = "q1". Means that should prob make it so you cant have zero states
    for (int i = 0; copy[i]; i++) {
        if (copy[i] == ',') count++;
    }

    dfa->num_states = count;

    dfa->states = malloc(count * sizeof(struct state));
    //add malloc success or fail check ? think that's good practice or something

    int i = 0;
    char *token = strtok(copy, ",");
	
	// MAYBE: check string isn't empty/too long/same name as other here?
    while (token != NULL && i < count) {
        strncpy(dfa->states[i].name, token, sizeof(dfa->states[i].name) - 1);
        dfa->states[i].name[sizeof(dfa->states[i].name) - 1] = '\0';
        //fail safe needed
        i++;
        token = strtok(NULL, ",");
    }

    free(copy);
    return 0;
}

int parse_fa_alphabet(struct dfa *dfa, char *alphabet_list, char *symbol_mappings) {
	
	char *copy = strdup(alphabet_list);
	
    int count = 1; //starts at one becuase state = "q1". Means that should prob make it so you cant have zero states
    for (int i = 0; copy[i]; i++) {
        if (copy[i] == ',') count++;
    }
	
	dfa->alphabet = malloc(count * sizeof(char));
	dfa->num_symbols = count;
	
    int i = 0;
    char *token = strtok(copy, ",");
	
	// MAYBE: check string isn't empty/too long/same name as other here?
	// need to only have single character strings here
    while (token != NULL && i < count) {
        
		char sym = token[0];
        dfa->alphabet[i] = sym;
		symbol_mappings[sym] = i;
        //fail safe needed
        i++;
        token = strtok(NULL, ",");
    }
	
	
	free(copy);
	return 0;
	
}

int parse_fa_transitions(struct dfa *dfa , char *transition_list, char *symbol_mappings) {

}

int parse_fa_start(struct dfa *dfa , char *start_state) {

    for (int i = 0; i < dfa->num_states; i++) {
        if (strcmp(dfa->states[i].name, start_state) == 0) { //check to make sure state exists
            dfa->start_state = i;
            return 0;
        }
    }

    return -1;
}

int parse_fa_end(struct dfa *dfa , char *end_state_list){ 

    char *copy = strdup(end_state_list);

    char *token = strtok(copy, ",");
    int end_state_length = 0;
    int found = 0;
    while (token) {
        end_state_length++;
        for (int i = 0; i < dfa->num_states; i++) {
            if (strcmp(dfa->states[i].name, token) == 0) {
                dfa->states[i].is_end = 1;
                found++;
                break;
            }
        }
        token = strtok(NULL, ",");

    }

    free(copy);

    if (found == end_state_length) {
        return 0;
    }

    return -1;
}
