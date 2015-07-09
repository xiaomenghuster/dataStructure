#include <stdio.h>
#include "myhead.h"
int main(){
	char chp[100];
	start();
	// gets(chp);
	index_1(chp);
}

void start(){
	printf("------------------------------------------\n");
	printf("| This the first string-index algorithm! |\n");
	printf("------------------------------------------\n");
}

void index_1(char* chp){
	FILE *fin;
	fin=fopen(FILENAME,"r");
	char c;
	while(c=fgetc(fin))
		putchar(c);
	// puts("hello xiaomeng, your sub_string is:");
	// puts(chp);
}