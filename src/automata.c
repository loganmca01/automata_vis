#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
#include "dpda.h"
#include "npda.h"

int main() {
	
	
	printf("test\n");
	
	char *states = "s1,s2";
	char *alphabet = "0,1";
	char *transitions = "s1,0,s2;s1,1,s1;s2,0,s1;s2,1,s2";
	char *start = "s1";
	char *end = "s2";
	
	create_dfa(states, alphabet, transitions, start, end);
	
	char *input_str = "0110100010";
	char *converted_input;
	initialize_dfa_sequence(input_str, &converted_input);
	
	int status;

	while((status = progress_dfa_sequence(converted_input)) == 0) {
		printf("ongoing\n");
	}

	printf("%d\n", status);
	
	free_dfa_mem(&converted_input);
	
}


/**

create_{name}
delete_{name}


**/
