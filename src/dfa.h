
#include "./def.h"

int create_dfa(char *state_list, char *alphabet_list, char *transition_list, char *start_state, char *end_state_list);

int initialize_dfa_sequence(char *original_input, char **converted_input);

int progress_dfa_sequence(char *input);

void free_dfa_mem(char **converted_input);

void log_dfa(unsigned char sym, unsigned char old);

void print_log();
/*

transition set is |states| x |symbols|

symbol lookup table is char[256]

initializing sequence translates symbols to int mapping so under the hood everything is treated as an int

on creation states are mapped to ints where the number is the location in the state array of the given state

this allows for more work to be done up front and quicker runtime of the state machines once created

this also helps for nfa's since when they split it will only be new ints to keep track of rather than pointers to states

potential issues:

verifying input, 

  0 1 2 3 4
0 x x x x x
1 y y y y y
2 z z z z z


xyzxyz
012012

state *iter
iter->loc;

char input = 'y';

char map[256];

map['y'] == 1;




int iter;
char input;

index[2][1];

*/