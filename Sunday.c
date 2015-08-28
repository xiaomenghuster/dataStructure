/*match_4
 *Sunday匹配算法
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
	match_4(head,str,0);
	
}

void start(){
	printf("------------------------------------------\n");
	printf("| This the string-match_4 algorithm!     |\n");
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
	h->next=NULL;
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
	//printf("move %d steps",steps);
	int i;
	for(i=0;head!=NULL&&i<steps;i++){
		head=head->next;
	}
	return head;
}

long match_4(node* head,char* str,long ppos){
	int  i=0,j,k;
	long pos=1;  //从当前位置开始计数，然后加上传进来的起始位置ppos
	node *cur;  
	char c;
	int strlength=strlen(str);
	cur = movesteps(head,strlength);//先往后移动一个模式串的长度
	j=strlength-1;  //定位到最后一个字符
	while(j>=0&&cur!=NULL){
		if(str[j]==cur->ch){
			cur=cur->pre;
			i++;
			j--;
		}
		else{
			cur = movesteps(cur,i+1);
			pos++;
			i=0;
			if(cur==NULL)
				break;   //到文档末尾则退出
			j=strlength-1;
			while(j>=0&&str[j]!=cur->ch){
				j--;
			}
			cur=movesteps(cur,strlength-j-1);
			pos=pos+strlength-j-1;
			j=strlength-1;
		}
	}
	
	if(j<0)
		printf("%d\n",pos+ppos);
	if(cur!=NULL)
		match_4(cur->next,str,pos+ppos);
	else
		return;
}