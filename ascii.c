/*随机产生一个名为ascii.txt的字符文件
 *作为匹配文件
 *[a-zA-Z0-9]
 */
 
#include"myhead.h"
#include<stdio.h>

void main(){
	long number;
	puts("How many character do you want to produce?");
	scanf("%d",&number);
	puts("The ascii.txt is being created...");
	puts("...");
	create(number);
	puts("The ascii.txt has being created.");
}

void create(long number){
	int select;
	char c;
	long i=0;
	FILE* fout= fopen(CONTENTFILE,"w");
	while(i<number){
		select=rand()%3+1;
		switch(select){
			case 1:
				c=rand()%26+97;
				//putchar(c);
				fputc(c,fout);
				break;
			case 2:
				c=rand()%26+65;
				// putchar(c);
				fputc(c,fout);
				break;
			case 3:
				c=rand()%10+48;
				// putchar(c);
				fputc(c,fout);
				break;
		}
		i++;
	}
	fclose(fout);
}
	
