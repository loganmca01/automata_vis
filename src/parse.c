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
