#include<stdio.h>
#include<string.h>
#include<time.h>
#include"myhead.h"

void main(){
	long place;
	int i=0,strlength;
	puts("please input the place and the strlength:");
	scanf("%d %d",&place,&strlength);	
	char str[strlength+1];
	FILE *fin;
	fin=fopen(CONTENTFILE,"r");
	char c;
	while(place>0){
		fgetc(fin);
		place--;
	}
	while(i<strlength){
		c=fgetc(fin);
		str[i]=c;
		i++;
	}
	str[strlength]='\0';
	puts(str);
}

