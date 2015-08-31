/*match_5
 *BoyerMoore匹配算法
 *
*/
#include <stdio.h>
#include "myhead.h"
#include <math.h>
#include<stdlib.h>
#include<string.h>
int main(){
	char str[1000];
	node *head,*p;
	start();
	if(!(head=(node*)malloc(sizeof(node))))
		return ERROR;
	init(head);
	while(1){
	printf("please input the string: ");
	//show(head); //初始化成功
	scanf("%s",str);
	match_5(head,str,0);
	}
	
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
		p->pre=h;  //需要能够双向链表
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

node* movesteps(node* head,int steps){
	int i;
	for(i=0;head!=NULL&&i<steps;i++){
		head=head->next;
	}
	return head;
}

void get_bmbc(char* str,int* bmbc){
	int i;
	char c;
	int strlength = strlen(str);
	for(i=0;i<128;i++){
		bmbc[i]=strlength;
	}
	for(i=0;i<strlength;i++){
		c=str[i];
		bmbc[c]=strlength-i;
		// printf("[%c]%d\n", c,bmbc[c]);
	}
}

void get_bmgs(char* str,int* bmgs){
	int i,j,p;
	int strlength = strlen(str);
	int suff[strlength];
	suff[strlength-1]=strlength;
	for(i=strlength-2;i>=0;i--){
		p=i;
		while(p>=0&&str[p]==str[strlength-1-i+p]){
			p--;
		}
		suff[i]=i-p;
	}
	// puts("suff:");
	/*for(i=0;i<strlength;i++){
		printf("suff[%d]%d\n", i,suff[i]);
	}*/
	//计算bmgs[]
	// puts("bmgs:");
	for(j=0;j<strlength;j++){
		bmgs[j]=strlength-1;		
	}
	for(j=0;j<strlength-1;j++){
		bmgs[strlength-1-suff[j]]=strlength-1-j;		
		//printf("[%d]%d\n",strlength-1-suff[j],strlength-1-j );
	}
}

long match_5(node* head,char* str,long ppos){
	int  i=0,j,k;
	long pos=1;  //从当前位置开始计数，然后加上传进来的起始位置ppos
	node *cur;  //last表示匹配上匹配串最后一个字符的位置
	char c;
	int strlength=strlen(str);
	// printf("%d\n",strlength );
	int bmbc[128];
/*	for(k=0;k<128;k++){
		printf("%d",bmbc[k] );
	}*/
	int bmgs[strlength];
	get_bmbc(str,bmbc);
	get_bmgs(str,bmgs);
	/*for(i=0;i<strlength;i++){
		printf("%c%d ",str[i],bmbc[str[i]] );
	}
	puts(" ");
	for(i=0;i<strlength;i++){
		printf("%3d",bmgs[i] );
	}*/

	//先往后移动一个模式串的长度
	cur = movesteps(head,strlength);
	if(cur==NULL)
		return;
	j=strlength-1;  //最后一个字符
	while(j>=0){
		//puts("start while");
		if(str[j]==cur->ch){
			cur=cur->pre;
			i++;
			//pos++;
			j--;
		}
		else{
			c=cur->ch;
			i+=max(bmbc[str[j]],bmgs[j]);
			pos+=max(bmbc[str[j]],bmgs[j]);
			// printf("i=%d\n",i );
			cur=movesteps(cur,i);
			if(cur==NULL){
				break;
			}
			// putchar(cur->ch);
			i=0;
			j=strlength-1;
		}
	}
	if(j<0)
		printf("%d\n",pos+ppos);
	else
		return;
}


//比较两个数的大小，返回较大的那个数
int max(int a,int b){
	return a>b?a:b;
}