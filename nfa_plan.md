# Plan for NFA implementation

## Options for Implementation

**-convert to dfa, then run**
**-simulate each possible branching path the nfa can take**
**-tree structure, bfs or shortest path search to find solution (if exists)**

We chose to first attempt the tree-based implementation, as it should in theory run the fastest. If time permits, other implementations may be tested with performance data collected to confirm this belief.

## Tree Implementation

### Overview

Each node holds information about the current status of the state machine:
Node = (state, input position). I refer to the combination of these elements as the "status" below.

Starting from the first node, (s0, char 0), a tree is built following a breadth first search of the possible options for progression of the nfa.

### Problems to figure out

1. Tracking path of nfa
	- idea: each node tracks the path that was taken to get there (high memory overhead)
	- idea: each node tracks the node it was reached from, then after completion, walk back to log the path taken.
2. Need to check for duplicate nodes, e.g. nfa has a loop that only takes empty chars to follow, therefore can reach same status (state, input position).
	- idea: store nodes somehow in a way that makes it easy to check if a node with certain values exists
	- idea: separate array of size |states| x |input| that stores ints (booleans) which track whether a node with the same status already exists
		- If a node already exists, then the current branch can be ignored because it would've been reached with a shorter or equally short path prior
	- idea: hash table where hash is constructed based off of node status 
3. Tree/graph data structure tend to be terribly innefficient with regard to cache usage
	- idea: arena allocation, custom malloc function
	- idea: flatten tree to array (I know this should be possible, but I think it gets extremely complex to work with)