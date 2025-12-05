

# Automata Visualization Project

## Overview

This project is designed to create an educational visualization tool for the different classes of automata learned in any theory of computation class. Ava Ginsberg and I have been planning this project for a while, and finally both have time to work on it. We hope to host this project online, and as such are focused heavily on optimization to let these machines run as effectively as possible in browser.

In order to maximize efficiency, we chose to implement the backend for this project in C. Pointer arithmetic allows for easy processing of state machines, and the static nature of the machine definitions let us enforce good practices for memory safety without much extra overhead. In order to use our C code on a website, we're diving into WebAssembly (wasm). Compiling to wasm lets us convert our C backend into something that can run in a browser without any extra steps. 

## Organization

/frontend
  - html, css, js, and wasm files for display and backend connection

/src
  - C files for automata backend and a bash script for running tests
 
/test_automata
  - test_dfa -- test .dfa files for various dfa's
  - test_input -- input files for running simple tests with script, require which dfa is being tested, input string for that dfa, and expected result
  
  - more tests will be added when other automata fully implemented
  
## DFA Implementation

### Parsing

Parse functions for each part of the formal definition of a DFA:
 - state list
 - input alphabet
 - transition functions (defined as start-state,symbol,end-state)
 - overall start state
 - list of accepting states

### Data Structures

The dfa struct stores all relevant information for a dfa. States are stored as an array, where each state is mapped to an index in the array. Symbols in the alphabet are also mapped to an index in an array. Transition functions are represented by a 2d array of characters of size |number of states| x |number of symbols|. To lookup a transition, the dfa retrieves the element at transition_set\[start state mapping\]\[symbol mapping\], making lookups happen in O(1) time.

## Plans going forward

### Frontend

We aim to create a minimal frontend visualization tool to be expanded on later. So far we have succeeded in connecting the wasm backend to a test frontend, and are able to run dfa's through it. The next step will be to design a graphical interface for showing off the state machine.


### NFA Implementation

We have discussed different ways to implement nfas in the nfa_plan.md document in this same directory. This will be the next step for the backend.


