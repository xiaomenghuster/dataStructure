/*
 *�ַ���ƥ���㷨
 *Main����
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
		//show(head); //��ʼ���ɹ�
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
		p->pre=h;  //��Ҫ�ܹ�˫������
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
	/* while(h->pre!=NULL){
		putchar(h->ch);
		h=h->pre;
	} */
}

void display(node* head,char* str){
	puts("finding end");
	puts("algorithm\t|   place / time(s)");
	puts("-------------------------------------");
	printf("%s","Brute Force\t| ");
	match_1(head,str,0);
	puts("");					//����
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
 * ��Ҫ�Ӻ�������
 */

long match_1(node* head,char* str,long ppos){
	//��ʱ
	struct timeval start,end;
	gettimeofday(&start,NULL);
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
		printf("  %d / ",pos+ppos);
	else 
		printf("no found! / ");
	gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);
	/* if(cur->next!=NULL)
		match_1(cur,str,pos+ppos+strlength);
	else 
		return 0; */
}

void get_next(char* str,int* next){
	int i=1,j=0;
	next[1]=0;
	int strlength = strlen(str)-1;//��һ��ȷ��Ϊ0
	while(i<strlength){
		if(j==0||str[i]==str[j]){
			i++;
			j++;
			next[i]=j;
			//printf("%d",next[i]);
		}
		else 
			j=next[j];
	}
}

long match_2(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int i=0,j=1;
	long pos=0;  //�ӵ�ǰλ�ÿ�ʼ������Ȼ����ϴ���������ʼλ��ppos
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	char str_2[strlength+2]; //���ǽ�����־�����ԼӶ�
	int next[strlength+1];
	while(str_2[i+1]=str[i])
		i++;  //���κ���һλ
	get_next(str_2,next);  //�õ�next����
	
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
}


node* movesteps(node* head,int steps){
	int i;
	for(i=0;head!=NULL&&i<steps;i++){
		head=head->next;
	}
	return head;
}

/* name:Horspool 
 * ��Ҫ�Ӻ�����movesteps
 */
long match_3(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int  i=0,j,k;
	long pos=1;  //�ӵ�ǰλ�ÿ�ʼ������Ȼ����ϴ���������ʼλ��ppos
	node *cur,*last;  //last��ʾƥ����ƥ�䴮���һ���ַ���λ��
	char c;
	int strlength=strlen(str);
	//�������ƶ�һ��ģʽ���ĳ���
	cur = movesteps(head,strlength);
	j=strlength-1;  //���һ���ַ�
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
				pos++;  //��¼λ��
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
 * ��Ҫ�Ӻ�����movesteps
 */

long match_4(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int  i=0,j,k;
	long pos=1;  //�ӵ�ǰλ�ÿ�ʼ������Ȼ����ϴ���������ʼλ��ppos
	node *cur;  
	char c;
	int strlength=strlen(str);
	cur = movesteps(head,strlength);//�������ƶ�һ��ģʽ���ĳ���
	j=strlength-1;  //��λ�����һ���ַ�
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
				break;   //���ĵ�ĩβ���˳�
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
 * ��Ҫ�Ӻ�����get_b
 */
long match_6(node* head,char* str,long ppos){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int i;
	int B[128]={0};
	long pos=1;  //�ӵ�ǰλ�ÿ�ʼ������Ȼ����ϴ���������ʼλ��ppos
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