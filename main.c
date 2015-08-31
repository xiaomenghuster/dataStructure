/*
 *脳脰路没麓庐脝楼脜盲脣茫路篓
 *Main潞炉脢媒
 *
*/
#include <stdio.h>
#include "myhead.h"
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main(){
	char str[1000];
	node *head,*p;
	start();
	if(!(head=(node*)malloc(sizeof(node))))
		return ERROR;
	init(head);
	while(1){
		printf("please input the string: \n");
		//show(head); //鲁玫脢录禄炉鲁脡鹿娄
		scanf("%s",str);
		display(head,str);
		puts("");
	}
	
}

void start(){
	printf(" ------------------------------------------\n");
	printf("| This the string-match algorithm!         |\n");
	printf(" ------------------------------------------\n");
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
		p->pre=h;  //脨猫脪陋脛脺鹿禄脣芦脧貌脕麓卤铆
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
	/* while(h->pre!=NULL){
		putchar(h->ch);
		h=h->pre;
	} */
}

void display(node* head,char* str){
	puts(" ");
	puts("finding results:");
	puts("algorithm\t|   place / time(s)");
	puts("-------------------------------------");
	printf("%s","Brute Force\t| ");
	match_1(head,str,0);
	puts("");					//禄禄脨脨
	printf("%s","KMP\t\t| ");
	match_2(head,str,0);
	puts("");
	printf("%s","Horspool\t| ");
	match_3(head,str,0);
	puts("");
	printf("%s","Sunday\t\t| ");
	match_4(head,str,0);
	puts("");
	printf("%s","Shift-And\t| ");
	match_6(head,str,0);
	puts("");
}

/* name:Brute Force 
 * 脨猫脪陋脳脫潞炉脢媒拢潞脦脼
 */

long match_1(node* head,char* str,long ppos){
	//录脝脢卤
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int  j=0;
	long pos=0;
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	if(strlength>1000){
		printf("  over length!");
		return;
	}
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
		printf("  %d / ",pos+ppos);
	else 
		printf("no found! / ");
	gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);
}

void get_next(char* str,int* next){
	// puts(str);
	int i=1,j=0,k=0;
	next[1]=0;
	int strlength = strlen(str);//碌脷脪禄赂枚脠路露篓脦陋0
	char str_2[strlength+2]; //驴录脗脟陆谩脢酶卤锚脰戮拢卢脣霉脪脭录脫露镁
	while(str_2[k+1]=str[k]){
		// putchar(str[k]);
		k++;
	}
	// puts(" ");
	while(i<strlength){
		if(j==0||str_2[i]==str_2[j]){
			i++;
			j++;
			next[i]=j;
			// printf("%d ",next[i]);
		}
		else 
			j=next[j];
	}
	// puts(" ");
}


//
long match_2(node* head,char* str,long ppos){
	// puts(str);
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int i=0,j=1;
	long pos=0;  //麓脫碌卤脟掳脦禄脰脙驴陋脢录录脝脢媒拢卢脠禄潞贸录脫脡脧麓芦陆酶脌麓碌脛脝冒脢录脦禄脰脙ppos
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	int next[strlength+1];
	/* char str_2[strlength+2]; //驴录脗脟陆谩脢酶卤锚脰戮拢卢脣霉脪脭录脫露镁
	while(str_2[i+1]=str[i]){
		i++;
		putchar(str_2[i]);
	}
	 */
	
	get_next(str,next);  //碌脙碌陆next潞炉脢媒
	while(j<=strlength&&cur->next!=NULL){
		if(j==0||str[j-1]==cur->ch){
			cur=cur->next;
			pos++;
			j++;
		}
		else{
			j=next[j]; //bug:next脢媒脳茅脙禄脫脨脮媒脠路脡煤鲁脡
		}
	}
	if(j>strlength)
		printf("  %d / ",pos+ppos-strlength);
	else 
		printf("no found! / ");
	gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);
}


node* movesteps(node* head,int steps){
	int i;
	for(i=0;head!=NULL&&i<steps;i++){
		head=head->next;
	}
	return head;
}

/* name:Horspool 
 * 脨猫脪陋脳脫潞炉脢媒拢潞movesteps
 */
long match_3(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int  i=0,j,k;
	long pos=1;  //麓脫碌卤脟掳脦禄脰脙驴陋脢录录脝脢媒拢卢脠禄潞贸录脫脡脧麓芦陆酶脌麓碌脛脝冒脢录脦禄脰脙ppos
	node *cur,*last;  //last卤铆脢戮脝楼脜盲脡脧脝楼脜盲麓庐脳卯潞贸脪禄赂枚脳脰路没碌脛脦禄脰脙
	char c;
	int strlength=strlen(str);
	if(strlength>1000){
		printf("  over length!");
		return;
	}
	//脧脠脥霉潞贸脪脝露炉脪禄赂枚脛拢脢陆麓庐碌脛鲁陇露脠
	cur = movesteps(head,strlength);
	j=strlength-1;  //脳卯潞贸脪禄赂枚脳脰路没
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
				pos++;  //录脟脗录脦禄脰脙
				j--;
			}
			cur = movesteps(cur,i);
			i=0;
			j=strlength-1;
		}
	}
	if(j<0)
		printf("  %d / ",pos+ppos);
	else 
		printf("no found! / ");
	gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);
	/* if(cur!=NULL)
		match_3(cur->next,str,pos+ppos);
	else 
		return; */
}

/* name:Sunday
 * 脨猫脪陋脳脫潞炉脢媒拢潞movesteps
 */

long match_4(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int  i=0,j,k;
	long pos=1;  //麓脫碌卤脟掳脦禄脰脙驴陋脢录录脝脢媒拢卢脠禄潞贸录脫脡脧麓芦陆酶脌麓碌脛脝冒脢录脦禄脰脙ppos
	node *cur;  
	char c;
	int strlength=strlen(str);
	if(strlength>1000){
		printf("  over length!");
		return;
	}
	cur = movesteps(head,strlength);//脧脠脥霉潞贸脪脝露炉脪禄赂枚脛拢脢陆麓庐碌脛鲁陇露脠
	j=strlength-1;  //露篓脦禄碌陆脳卯潞贸脪禄赂枚脳脰路没
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
				break;   //碌陆脦脛碌碌脛漏脦虏脭貌脥脣鲁枚
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
		printf("  %d / ",pos+ppos);
	else 
		printf("no found! / ");
	gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);
	/* if(cur!=NULL)
		match_4(cur->next,str,pos+ppos);
	else
		return; */
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

/* name:Shift-And
 * 脨猫脪陋脳脫潞炉脢媒拢潞get_b
 */
long match_6(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int i;
	int B[128]={0};
	long pos=1;  //麓脫碌卤脟掳脦禄脰脙驴陋脢录录脝脢媒拢卢脠禄潞贸录脫脡脧麓芦陆酶脌麓碌脛脝冒脢录脦禄脰脙ppos
	int strlength=strlen(str);
	if(strlength>32){
		printf("  over length!");
		return;
	}
	long long D=0,mask;
	mask = 1<<(strlength-1);
	node* cur=head->next;
	get_b(str,B);
	while(cur!=NULL){
		D=(D<<1|1)&B[cur->ch];
		//printf("%x\n",D);
		cur=cur->next;
		pos++;
		if(D&mask)
			break;
	}
	if(D&mask)
		printf("  %d / ",pos+ppos-strlength);
	else 
		printf("no found! / ");
	gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);
		//printf("find");
	/* if(cur!=NULL)
		match_6(cur,str,pos+ppos);
	else 
		return;
	 */
}