/*match_5
 *Shift-And/Shift-Or匹配算法
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
	//get_b(str,B);
	match_6(head,str,0);
}

void start(){
	printf("------------------------------------------\n");
	printf("| This the string-match_5 algorithm!     |\n");
	printf("------------------------------------------\n");
}

int init(node* head){
	head->pre=NULL;
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
		p->pre=h;  //需要双向链表
		h=p;
		//putchar(c);
	}
	p->next=NULL;
} 

void show(node* h){
	h=h->next;
	while(h->next!=NULL){
		//putchar(h->ch);
		h=h->next;
	}
	while(h->pre!=NULL){
		putchar(h->ch);
		h=h->pre;
	}
}

/*
 *将链表指针往后移动
 *参数为往后移动的步数
 */
node* movesteps(node* head,int steps){
	int i;
	for(i=0;head!=NULL&&i<steps;i++){
		head=head->next;
	}
	return head;
}

void get_b(char* str,int* B){
	int i,j;
	unsigned int shift=1;
	int strlength=strlen(str);
	for(i=0;i<strlength;i++){
		B[str[i]]|=shift;
		shift<<=1;
	}
	/*
	for(i=0;i<strlength;i++){
		printf("%c%x\n",str[i],B[str[i]]);
	}*/
}

long match_6(node* head,char* str,long ppos){
	int i;
	int B[128]={0};
	long pos=1;  //从当前位置开始计数，然后加上传进来的起始位置ppos
	int strlength=strlen(str);
	unsigned long D=0,mask;
	mask = 1<<strlength-1;
	node* cur=head->next;
	get_b(str,B);
	while(cur!=NULL){
		D=(D<<1|1)&B[cur->ch];
		//printf("%x\n",D);
		pos++;
		if(D&mask)
			break;
		cur=cur->next;
	}
	if(D&mask)
		printf("%d\n",pos+ppos-strlength);
		//printf("find");
	if(cur!=NULL)
		match_6(cur,str,pos+ppos-1);
	else 
		return;
	
}