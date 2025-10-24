#ifndef DEF
#define DEF


//!! NOTE: for nfas, going to need to track both state and location in string for each branch

struct state {
	char name[16]; //better as strict array or pointer?
	int is_end;
	int loc;
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