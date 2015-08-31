/*match_2
 *KMP匹配算法
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
	while(1){
	printf("please input the string: ");
	//show(head); //初始化成功
	scanf("%s",str);
	//printf("%d",match_2(head,str));
		// match_2(head,str,0);
		display(head,str);
	}
}

void display(node* head,char* str){
	char* str_2 =str;
	match_2(head,str_2,0);
}

void start(){
	printf("------------------------------------------\n");
	printf("| This the string-match_2 algorithm!     |\n");
	printf("------------------------------------------\n");
}

int init(node* head){
	node *h=head,*p;
	FILE *fin;
	fin=fopen(CONTENTFILE,"r");
	char c;
	while(!feof(fin)){
		c=fgetc(fin);
		if(!(p=(node*)malloc(sizeof(node))))
			return ERROR;
		p->ch=c;
		h->next=p;
		h=p;
		//putchar(c);
	}
	h->next=NULL;
} 

void show(node* h){
	h=h->next;
	while(h->next!=NULL){
		putchar(h->ch);
		h=h->next;
	}
}

void get_next(char* str,int* next){
	int i=1,j=0;
	next[1]=0;
	int strlength = strlen(str)-1;//第一个确定为0
	while(i<strlength){
		if(j==0||str[i]==str[j]){
			i++;
			j++;
			next[i]=j;
			printf("%d ",next[i]);
		}
		else 
			j=next[j];
	}
	puts(" ");
}

long match_2(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int i=0,j=1;
	long pos=0;  //从当前位置开始计数，然后加上传进来的起始位置ppos
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	char str_2[strlength+2]; //考虑结束标志，所以加二
	int next[strlength+1];
	while(str_2[i+1]=str[i])
		i++;  //依次后移一位
	get_next(str_2,next);  //得到next函数
	
	while(j<=strlength&&cur->next!=NULL){
		if(j==0||str_2[j]==cur->ch){
			cur=cur->next;
			pos++;
			j++;
		}
		else{
			j=next[j];
		}
	}
	if(j>strlength)
		printf("  %d / ",pos+ppos-strlength);
	else 
		printf("no found! / ");
	gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);
	puts(" ");
	
}


/* void get_next(char* str,int* next){
	int i=1,j=0;
	next[1]=0;
	int strlength = strlen(str)-1;//第一个确定为0
	while(i<strlength){
		if(j==0||str[i]==str[j]){
			i++;
			j++;
			next[i]=j;
			printf("%d ",next[i]);
		}
		else 
			j=next[j];
	}
	puts(" ");
}

long match_2(node* head,char* str,long ppos){
	int i=0,j=1;
	long pos=0;  //从当前位置开始计数，然后加上传进来的起始位置ppos
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	char str_2[strlength+2]; //考虑结束标志，所以加二
	int next[strlength+1];
	while(str_2[i+1]=str[i])
		i++;  //依次后移一位
	get_next(str_2,next);  //得到next函数
	
	while(j<=strlength&&cur->next!=NULL){
		if(j==0||str_2[j]==cur->ch){
			cur=cur->next;
			pos++;
			j++;
		}
		else{
			j=next[j];
		}
	}
	if(j>strlength)
		printf("%d\n",pos+ppos-strlength);
	else
		printf("no find!\n");
	
} */
