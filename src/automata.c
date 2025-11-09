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
	
	if (argc != 4) {
		printf("error, need cmd line arg file name\n");
		exit(1);
	}

	FILE *f = fopen(argv[1], "r");
	if (f == 0) {
		printf("%s\n", argv[1]);
		printf("error opening file\n");
		exit(1);
	}

	char *states = NULL;
	char *alphabet = NULL;
	char *transitions = NULL;
	char *start = NULL;
	char *end = NULL;
	size_t len = 64;

	if (getline(&states, &len, f) == -1 ||
		getline(&alphabet, &len, f) == -1 ||
		getline(&transitions, &len, f) == -1 ||
		getline(&start, &len, f) == -1 ||
		getline(&end, &len, f) == -1) {
			fprintf(stderr, "Error: file missing lines or malformed.\n");
			return 0;
	}
	

	remove_newline_windows_weirdness(states);
	remove_newline_windows_weirdness(alphabet);
	remove_newline_windows_weirdness(transitions);
	remove_newline_windows_weirdness(start);
	remove_newline_windows_weirdness(end);

	if (create_dfa(states, alphabet, transitions, start, end) == -1) {
		printf("creation error\n");
		exit(1);
	}

	char *converted_input;
	initialize_dfa_sequence(&argv[2][0], &converted_input);

	int status;

	while((status = progress_dfa_sequence(converted_input)) == 0) {
		continue;
	}
	if (status == 1) {
		printf("denied\n");
	}
	else if (status == 2) {
		printf("accepted\n");
	}
	
	if (argv[3][0] == '1') {
		print_dfa_log();
	}
	
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

