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
    int location = 0;
    while (token != NULL && i < count) {
        strncpy(dfa->states[i].name, token, sizeof(dfa->states[i].name) - 1);
        dfa->states[i].name[sizeof(dfa->states[i].name) - 1] = '\0';
        dfa->states[i].location = location;
        location++;
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

int parse_fa_transitions(struct dfa *dfa, char *transition_list, char *symbol_mappings) {

    int state_size = dfa->num_states;
    int alph_size = dfa->num_symbols;

    dfa->transition_set = malloc(state_size * sizeof(char *));
    for (int i = 0; i < state_size; i++) {
        dfa->transition_set[i] = malloc(alph_size * sizeof(char));
    }

    // Make a copy of the input so strtok doesn’t modify the original
    char *copy = strdup(transition_list);
    char *token = strtok(copy, ";");
    int i = 0;

    // Each token looks like: "q0,a,q1"  (meaning from q0 on 'a' -> q1)
    while (token != NULL) {
        char from[64], symbol[64], to[64];
        if (sscanf(token, "%63[^,],%1[^,],%63s", from, symbol, to) == 3) {
            int from_index = -1;
            int to_index = -1;

            // find the state indices by name
            for (int s = 0; s < dfa->num_states; s++) {
                if (strcmp(dfa->states[s].name, from) == 0)
                    from_index = s;
                if (strcmp(dfa->states[s].name, to) == 0)
                    to_index = s;
            }

            if (from_index != -1 && to_index != -1) {
                char sym = symbol[0];  // take first char of symbol

                // TODO: check that symbol is valid, need to work on table a bit
                dfa->transition_set[from_index][symbol_mappings[sym]] = to_index;
            } else {
                fprintf(stderr, "Error: invalid transition '%s'\n", token);
                return -1;
            }
        } else {
            fprintf(stderr, "Error parsing transition token: %s\n", token);
            return -1;
        }

        token = strtok(NULL, ";");
        i++;
    }

    free(copy);
    return 0;
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
