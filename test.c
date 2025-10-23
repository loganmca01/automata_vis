#include <stdio.h>

int arr[4];

int main(){
	return 0;
}

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