#ifndef DEF
#define DEF

// macros for dfa logging
#define DFA_LOG_START_STATE 0xff
#define DFA_LOG_END_STATE 0xff00
#define DFA_LOG_SYMBOL 0xff0000

#define GET_DFA_LOG_START_STATE(x) ((unsigned char)((x) & (0xff)))
#define GET_DFA_LOG_END_STATE(x) ((unsigned char)((x) & (0xff00) >> 8))
#define GET_DFA_LOG_SYMBOL(x) ((unsigned char)((x) & (0xff0000) >> 16))


//!! NOTE: for nfas, going to need to track both state and location in string for each branch

struct state {
	char name[16]; //better as strict array or pointer?
	int is_end;
	int location; //using this for array now
};


struct dfa {
	
	struct state *states;
	char *alphabet;
	
	// can use chars here? will that require a conversion for comparisons?
	int num_states;
	int num_symbols;
	
	char **transition_set;
	
	int start_state;

	/* end state info instead stored directly in state struct */
	//struct state *start; // TODO: determine if its faster to include this extra memory here or just go through states to check for start
	//char **end;
	//int num_ends;
	
};

#endif /* DEF */