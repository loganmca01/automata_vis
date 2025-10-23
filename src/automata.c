#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
#include "dpda.h"
#include "npda.h"

int main() {
	
	
	printf("test\n");
	
	struct dfa *dfa;
	char *symbol_mappings;
	
	char *states = "s1,s2,s3";
	char *alphabet = "0,1";
	char *transitions = "yeah idk";
	char *start = "s1";
	char *end = "s3";
	
	create_dfa(&dfa, states, alphabet, transitions, start, end, &symbol_mappings);
	
	char *input_str = "01101";
	char *converted_input;
	initialize_dfa_sequence(&dfa, input_str, &converted_input, &symbol_mappings);
	
	while(progress_dfa_sequence(&dfa, converted_input) == 0) {
		printf("something like this");
	}
	
	free_dfa_mem(&dfa, &symbol_mappings, &converted_input);
	
}


/**

create_{name}
delete_{name}


**/
