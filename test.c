#include <stdio.h>
#include "./src/def.h"
#include <stdlib.h>

int arr[4];

int main(){
	
	struct dfa *d = malloc(1 * sizeof(struct dfa));
	struct dfa **m = &d;
	
	d->start_state = 5;
	
	printf("%d\n", (*m)->start_state);
	
	free(d);
	return 0;
	
}
/*
void fun1() {
	
	int x = 1;
	
	printf("%d\n", arr[x]);

}

void fun2() {
	
	char x = 1;
	
	printf("%d\n", arr[x]);
	
}

void fun3() {
	
	size_t x = 1;
	
	printf("%d\n", arr[x]);
	
}

void fun4() {
	
	long x = 1;
	
	printf("%d\n", arr[x]);
	
}
*/