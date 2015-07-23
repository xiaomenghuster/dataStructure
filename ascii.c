/*随机产生一个名为ascii.txt的字符文件
 *作为匹配文件
 *[a-zA-Z0-9]
 */
 
#include"myhead.h"
#include<stdio.h>

void main(){
	long number;
	int choice;
	printf("----------------------------------------------------\n");
	printf("|  which kind of ascii.txt do you want to create?  |\n");
	printf("|  1:[01]    2:[0-9]    3:[a-z]    4:[a-z0-9A-Z]   |\n"); 
	printf("----------------------------------------------------\n");
	printf("your choice: ");
	scanf("%d",&choice);
	puts("How many character do you want to produce?");
	scanf("%d",&number);
	puts("The ascii.txt is being created...");
	puts("...");
	create(choice,number);
	puts("The ascii.txt has being created.");
}

void create(int choice,long number){
	char c;
	int kind;
	long i=0;
	FILE* fout= fopen(CONTENTFILE,"w");
	while(i<number){
		switch(choice){
			case 1:
				c=rand()%2+'0';
				//putchar(c);
				fputc(c,fout);
				break;
			case 2:
				c=rand()%10+48;
				// putchar(c);
				fputc(c,fout);
				break;
			case 3:
				c=rand()%26+97;
				// putchar(c);
				fputc(c,fout);
				break;
			case 4:
				kind=rand()%3+1;
				switch(kind){
					case 1:
						c=rand()%10+'0';
						break;
					case 2:
						c=rand()%26+'a';
						break;
					case 3:
						c=rand()%26+'A';
						break;
					default:
						break;
				}
				fputc(c,fout);
				break;
			default:
				break;
		}
		i++;
	}
	fclose(fout);
}
	
