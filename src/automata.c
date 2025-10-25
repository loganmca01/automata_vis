#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dfa.h"
#include "nfa.h"
#include "dpda.h"
#include "npda.h"

int main(int argc, char **argv) {
	
	if (argc != 2) {
		printf("error, need cmd line arg file name\n");
		exit(1);
	}

	FILE *f = fopen(argv[1], "r");
	if (f == 0) {
		printf("error opening file\n");
		exit(1);
	}

	char *states = NULL;
	char *alphabet = NULL;
	char *transitions = NULL;
	char *start = NULL;
	char *end = NULL;
	size_t len = 64;

	getline(&states, &len, f);
	getline(&alphabet, &len, f);
	getline(&transitions, &len, f);
	getline(&start, &len, f);
	getline(&end, &len, f);

	if (states[strlen(states) - 1] == '\n' || states[strlen(states) - 1] == '\r' || states[strlen(states) - 1] == '\t') states[strlen(states) - 1] = 0;
	if (alphabet[strlen(alphabet) - 1] == '\n' || alphabet[strlen(alphabet) - 1] == '\r' || alphabet[strlen(alphabet) - 1] == '\t') alphabet[strlen(alphabet) - 1] = 0;
	if (transitions[strlen(transitions) - 1] == '\n' || transitions[strlen(transitions) - 1] == '\r' || transitions[strlen(transitions) - 1] == '\t') transitions[strlen(transitions) - 1] = 0;
	if (start[strlen(start) - 1] == '\n' || start[strlen(start) - 1] == '\r' || start[strlen(start) - 1] == '\t') start[strlen(start) - 1] = 0;
	if (end[strlen(end) - 1] == '\n' || end[strlen(end) - 1] == '\r' || end[strlen(end) - 1] == '\t') end[strlen(end) - 1] = 0;

	printf("%s\n", states);
	printf("%s\n", alphabet);
	printf("%s\n", transitions);
	printf("%s\n", start);
	printf("%s\n", end);

	printf("test\n");
	printf("%s\n", states);

	if (create_dfa(states, alphabet, transitions, start, end) == -1) {
		printf("creation error\n");
		exit(1);
	}

	printf("test2\n");


	char *input_str = "0110100010";
	char *converted_input;
	initialize_dfa_sequence(input_str, &converted_input);

	int status;

	while((status = progress_dfa_sequence(converted_input)) == 0) {
		printf("ongoing\n");
	}

	printf("%d\n", status);
	
	free_dfa_mem(&converted_input);

	free(states);
	free(alphabet);
	free(transitions);
	free(start);
	free(end);

	return 0;
	
	
}


/**

create_{name}
delete_{name}


**/
