/*match_1
 *普通匹配算法
 *
*/
#include <stdio.h>
#include "myhead.h"
#include<stdlib.h>
#include<string.h>
int main(){
	char str[100];
	node *head,*p;
	start();
	if(!(head=(node*)malloc(sizeof(node))))
		return ERROR;
	init(head);
	printf("please input the string: ");
	//show(head); //初始化成功
	scanf("%s",str);
	//printf("%d",match_1(head,str));
	match_1(head,str,0);
}

void start(){
	printf("------------------------------------------\n");
	printf("| This the string-match_1 algorithm!     |\n");
	printf("------------------------------------------\n");
}

int init(node* head){
	long length=0;
	node *h=head,*p;
	FILE *fin;
	fin=fopen(CONTENTFILE,"r");
	char c;
	while(!feof(fin)){
		length++;
		c=fgetc(fin);
		if(!(p=(node*)malloc(sizeof(node))))
			return ERROR;
		p->ch=c;
		h->next=p;
		h=p;
		//putchar(c);
	}
} 

void show(node* h){
	h=h->next;
	while(h->next!=NULL){
		putchar(h->ch);
		h=h->next;
	}
}

long match_1(node* head,char* str,long ppos){
	int  j=0;
	long pos=0;
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	while(j<strlength&&cur->next!=NULL){
		if(str[j]==cur->ch){
			cur=cur->next;
			j++;
		}
		else{
			j=0;
			pos++;
			cur=pre->next;
			pre=cur;
		}
			
	}
	if(j==strlength)
		printf("%d\n",pos+ppos);
	if(cur->next!=NULL)
		match_1(cur,str,pos+ppos+strlength);
	else 
		return 0;
}