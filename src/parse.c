#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //reminder to figure out if here or header or not needed becuase it's in main

// NOTE: I was trying to figure out the best way to track what memory is allocated so we don't have errors freeing stuff that
// wasn't malloced, decided the best was is for each of these functions to just free the memory they've allocated if they fail and
// made it so that happens.

int parse_fa_states(struct dfa *dfa, char *state_list) {
    char *copy = strdup(state_list);
    //add check if copy fails?
    int count = 1; 
    if (!copy[0]) {
        free(copy);
        fprintf(stderr, "Error: No valid end states possible\n");
        return -1;
    }; //prevents zero states

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
        for (int j = 0; j < i; j++) { //O(n^2) for the love of god replace this with a hashmap 
            if (strcmp(dfa->states[j].name, token) == 0) {
                fprintf(stderr, "Duplicate state name %s\n", token);
                free(copy);
                free(dfa->states);
                return -1;
            }
        }
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

int parse_fa_alphabet(struct dfa *dfa, char *alphabet_list, unsigned char *symbol_mappings) {
	
	char *copy = strdup(alphabet_list);
	
    int count = 1; 
    if (!copy[0]) count = 0;
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
        if (strlen(token) != 1) {
            free(copy);
            free(dfa->alphabet);
            return -1;
        }
		else if ((unsigned char) token[0] == 255) {
            free(copy);
            free(dfa->alphabet);
            return -1;
		}
        for (int j = 0; j < i; j++) { //replace with hashmap
            if (dfa->alphabet[j] == token[0]) {
                fprintf(stderr, "Duplicate input symbol %s\n", token);
                free(copy);
                free(dfa->alphabet);
                return -1;
            }
        }
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

int parse_fa_transitions(struct dfa *dfa, char *transition_list, unsigned char *symbol_mappings) {

    int state_size = dfa->num_states;
    int alph_size = dfa->num_symbols;

    dfa->transition_set = malloc(state_size * sizeof(char *));
    for (int i = 0; i < state_size; i++) {
        dfa->transition_set[i] = malloc(alph_size * sizeof(char));
    }

    char *copy = strdup(transition_list);
    char *token = strtok(copy, ";");
    int i = 0;

    // Each token looks like: "q0,a,q1"  (meaning from q0 on 'a' -> q1)
    while (token != NULL) {
        char from[64], symbol[2], to[64];
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
                int mapped = symbol_mappings[sym];
                if (mapped == 255) {
                    fprintf(stderr, "Error: Invalid character in transition function %c\n", sym);
                    free(copy);
                    for (int s = 0; s < state_size; s++) {
                        free(dfa->transition_set[s]);
                    }
                    free(dfa->transition_set);                    
                    return -1;
                }
                dfa->transition_set[from_index][mapped] = to_index;
            } else {
                fprintf(stderr, "Error: invalid transition '%s'\n", token);
				free(copy);
                for (int s = 0; s < state_size; s++) {
                    free(dfa->transition_set[s]);
                }
                free(dfa->transition_set);
                
				free(dfa->transition_set);
                return -1;
            }
        } else {
            fprintf(stderr, "Error parsing transition token: %s\n", token);
			free(copy);
            for (int s = 0; s < state_size; s++) {
                free(dfa->transition_set[s]);
            }
            free(dfa->transition_set);
            
			free(dfa->transition_set);
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

    fprintf(stderr, "Invalid start state\n"); 
    return -1;
}

int parse_fa_end(struct dfa *dfa , char *end_state_list){ 

    char *copy = strdup(end_state_list);

    char *token = strtok(copy, ",");
    while (token) { 
        for (int i = 0; i < dfa->num_states; i++) {
            if (strcmp(dfa->states[i].name, token) == 0) {
                dfa->states[i].is_end = 1;
                break;
            }
            if (i == dfa->num_states - 1) {
                free(copy);
                fprintf(stderr, "Error: Invalid endstate %s\n", token);
                return -1;
            }
        }
        token = strtok(NULL, ",");

    }

    free(copy);

    return 0;
}
