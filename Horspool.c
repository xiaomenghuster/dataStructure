/*match_3
 *Horspool匹配算法
 *
*/
#include <stdio.h>
#include "myhead.h"
#include<stdlib.h>
#include<string.h>
int main(){
	char str[1000];
	node *head,*p;
	start();
	if(!(head=(node*)malloc(sizeof(node))))
		return ERROR;
	init(head);
	printf("please input the string: ");
	//show(head); //初始化成功
	scanf("%s",str);
	match_3(head,str,0);
	
}

void start(){
	printf("------------------------------------------\n");
	printf("| This the string-match_3 algorithm!     |\n");
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
		p->pre=h;  //需要能够双向链表
		h=p;
		//putchar(c);
	}
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

node* movesteps(node* head,int steps){
	int i;
	for(i=0;head!=NULL&&i<steps;i++){
		head=head->next;
	}
	return head;
}

long match_3(node* head,char* str,long ppos){
	int  i=0,j,k;
	long pos=1;  //从当前位置开始计数，然后加上传进来的起始位置ppos
	node *cur,*last;  //last表示匹配上匹配串最后一个字符的位置
	char c;
	int strlength=strlen(str);
	//先往后移动一个模式串的长度
	cur = movesteps(head,strlength);
	j=strlength-1;  //最后一个字符
	while(j>=0&&cur!=NULL){
		if(str[j]==cur->ch){
			cur=cur->pre;
			i++;
			//pos++;
			j--;
		}
		else{
			c=cur->ch;
			while(j>=0&&str[j]!=c&&cur!=NULL){
				cur=cur->next;
				pos++;  //记录位置
				j--;
			}
			cur = movesteps(cur,i);
			i=0;
			j=strlength-1;
		}
	}
	if(j<0)
		printf("%d\n",pos+ppos);
	if(cur!=NULL)
		match_3(cur->next,str,pos+ppos);
	else 
		return;
	/*if(j>strlength)
		//return pos-strlength;
		printf("%d\n",pos+ppos-strlength);
	if(cur->next!=NULL)
		match_3(cur,str,pos+ppos);
	else
		return 0;
	*/
}