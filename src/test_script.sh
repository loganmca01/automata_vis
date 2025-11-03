#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
i=1

while read -r dfafile input result; do
	
	printf "test %d: " "$i"
	
	out=$(./automata $dfafile $input "0")
	
	if [[ "$out" == "$result" ]]; then
		printf "${GREEN}success\n${NC}"
	else
		printf "${RED}failure\n${NC}"
	fi
	
	((i++))
	
done < "$1"