#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
#include "dpda.h"
#include "npda.h"

int main() {
	
	
	printf("test\n");
	
	char *states = "s1,s2,s3";
	char *alphabet = "0,1";
	char *transitions = "yeah idk";
	char *start = "s1";
	char *end = "s3";
	
	create_dfa(states, alphabet, transitions, start, end);
	
	char *input_str = "01101";
	char *converted_input;
	initialize_dfa_sequence(input_str, &converted_input);
	
	while(progress_dfa_sequence(converted_input) == 0) {
		printf("something like this");
	}
	
	free_dfa_mem(&converted_input);
	
}


/**

create_{name}
delete_{name}


**/
