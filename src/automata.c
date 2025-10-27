#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dfa.h"
#include "nfa.h"
#include "dpda.h"
#include "npda.h"

void print_indiv_chars(char *in);
void remove_newline_windows_weirdness(char *str);

int main(int argc, char **argv) {
	
	if (argc != 3) {
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

	/*
	if (states[strlen(states) - 1] == '\n' || states[strlen(states) - 1] == '\r' || states[strlen(states) - 1] == '\t') states[strlen(states) - 1] = 0;
	if (alphabet[strlen(alphabet) - 1] == '\n' || alphabet[strlen(alphabet) - 1] == '\r' || alphabet[strlen(alphabet) - 1] == '\t') alphabet[strlen(alphabet) - 1] = 0;
	if (transitions[strlen(transitions) - 1] == '\n' || transitions[strlen(transitions) - 1] == '\r' || transitions[strlen(transitions) - 1] == '\t') transitions[strlen(transitions) - 1] = 0;
	if (start[strlen(start) - 1] == '\n' || start[strlen(start) - 1] == '\r' || start[strlen(start) - 1] == '\t') start[strlen(start) - 1] = 0;
	if (end[strlen(end) - 1] == '\n' || end[strlen(end) - 1] == '\r' || end[strlen(end) - 1] == '\t') end[strlen(end) - 1] = 0;
	*/


	

	remove_newline_windows_weirdness(states);
	remove_newline_windows_weirdness(alphabet);
	remove_newline_windows_weirdness(transitions);
	remove_newline_windows_weirdness(start);
	remove_newline_windows_weirdness(end);

	/*
	printf("%s\n", states);
 	print_indiv_chars(states);
	printf("%s\n", alphabet);
	print_indiv_chars(alphabet);
	printf("%s\n", transitions);
	print_indiv_chars(transitions);
	printf("%s\n", start);
	print_indiv_chars(start);
	printf("%s\n", end);
	print_indiv_chars(end);
	*/

	if (create_dfa(states, alphabet, transitions, start, end) == -1) {
		printf("creation error\n");
		exit(1);
	}

	printf("test\n");

	char *converted_input;
	initialize_dfa_sequence(&argv[2][0], &converted_input);

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

void print_indiv_chars(char *in) {

	int len = strlen(in);

	for (int i = 0; i < len; i++) {
		printf("%d\n", in[i]);
	}


}

void remove_newline_windows_weirdness(char *str) {

	while(*str != '\0') {
		if ((*str == '\r') || (*str == '\n')) {
			*str = '\0';
		}
		str++;
	}

}

/**

create_{name}
delete_{name}


**/
