/*writor:xiaomenghuster  date:summer
 *数据结构课程设计
 *五种字符串匹配算法
 *寻找所有匹配的字符串位置，没有则输出no find!
 *shift and 只能寻找32个字符以内的字符串，其他的最多为1000
*/
#include <stdio.h>
#include "myhead.h"
#include<stdlib.h>
#include<string.h>
#include<time.h>
long time_whole[6];  //总时间 bf,kmp,horspool,sunday,bm,shift
int main(){
	int i;
	for(i=0;i<6;i++)
		time_whole[i]=0;
	char str[1000];  //最多可以传入1000个字符，但是其中Shift-And算法最多只能处理32个字符
	int strlength,test_times,choice,iof;
	long number,place;
	node *head,*p;
	start();  //输出程序提示信息
	
	//init(head);//读取文件内容，初始化链表

	printf("--------------------------------------------------------\n");
	printf("|  input the string or find the string from ascii.txt  |\n");
	printf("|  1:find in ascii.txt      2:input the string         |\n"); 
	printf("--------------------------------------------------------\n");
	scanf("%d",&iof);
	switch(iof){
		case 1:  //先生成字符集文件，然后再在文件中指定位置寻找字符串
			printf("----------------------------------------------------\n");
			printf("|  which kind of ascii.txt do you want to create?  |\n");
			printf("|  1:[01]    2:[0-9]    3:[a-z]    4:[a-z0-9A-Z]   |\n"); 
			printf("----------------------------------------------------\n");
			printf("your choice: ");
			scanf("%d",&choice);
			puts("How many character do you want to produce?");
			scanf("%d",&number);

			puts("please input the place and the strlength:");
			scanf("%d %d",&place,&strlength);

		    puts("please input the test times:");
			scanf("%d",&test_times);
			int test_times_save=test_times;

			// getstring(place,strlength,str);
			while(test_times_save>0){   //使用test_time_save保存test_time的数值
				create(choice,number);  //形成字符集文件
				getstring(place,strlength,str);  //得到目标字符串
				puts("the string: ");
				puts(str);   //显示字符串
				if(!(head=(node*)malloc(sizeof(node))))
					return ERROR;
				init(head);			//初始化双向链表 
				display(head,str);  //调用匹配函数并输出结果
				puts("");
				test_times_save--;
			}
			break;
		case 2:
			puts("please input the string:");
			scanf("%s",str);
			test_times=1;
			//create(choice,number);  //形成字符集文件
			puts(str);
			if(!(head=(node*)malloc(sizeof(node))))
				return ERROR;
			init(head);			//初始化双向链表 
			display(head,str);  //调用匹配函数并输出结果
			puts("");
			break;
		default: break;
	}
	showresult(test_times);
}

void start(){
	printf(" ------------------------------------------\n");
	printf("| This the string-match algorithm!         |\n");
	printf("| Auther:xiaomeng                          |\n");
	printf("| Date:2015.9.21                           |\n");
	printf("|-----------all right reserve--------------|\n");
	printf(" ------------------------------------------\n");

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
		if(!(i%10000))
			fputc('\n',fout);
		i++;
	}
	fclose(fout);
}

void getstring(long place,int strlength,char* str){
	FILE *fin;
	int i=0;
	char c;
	fin=fopen(CONTENTFILE,"r");
	while(place>1){
		fgetc(fin);
		place--;
	}
	while(i<strlength){
		c=fgetc(fin);
		str[i]=c;
		i++;
	}
	str[strlength]='\0';

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
		p->pre=h;  //个别匹配算法需要双向链表
		h=p;
		//putchar(c);
	}
	h->next=NULL;
} 

void show(node* h){   //显示双向链表，测试生成情况
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
	struct timeval start,end;
	long bf_time,kmp_time,Horspool_time,Sunday_time,bm_time,shift_time;
	puts(" ");
	puts("finding results:");
	
	printf("%s","Brute Force\t| ");
	gettimeofday(&start,NULL);  //得到开始时间
	match_1(head,str,0);
	gettimeofday(&end,NULL);  //得到结束时间
	bf_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //计算经过的时间
	//printf("%f",timeuse/1000000.0);
	time_whole[0]+=bf_time;  //时间累加
	puts("");					//换行
	puts("");

	printf("%s","KMP\t\t| ");
	gettimeofday(&start,NULL);  //得到开始时间
	match_2(head,str,0);
	gettimeofday(&end,NULL);  //得到结束时间
	kmp_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //计算经过的时间
	// printf("%f",timeuse/1000000.0);
	time_whole[1]+=kmp_time;
	puts("");
	puts("");					//换行

	printf("%s","Horspool\t| ");
	gettimeofday(&start,NULL);
	match_3(head,str,0);
	gettimeofday(&end,NULL);  //得到结束时间
	Horspool_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //计算经过的时间
	// printf("%f",timeuse/1000000.0);
	time_whole[2]+=Horspool_time;
	puts("");
	puts("");

	printf("%s","Sunday\t\t| ");
	gettimeofday(&start,NULL);
	match_4(head,str,0);
	gettimeofday(&end,NULL);  //得到结束时间
	Sunday_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //计算经过的时间
	// printf("%f",timeuse/1000000.0);
	time_whole[3]+=Sunday_time;
	puts("");
	puts("");

	printf("%s", "BoyerMoore\t| ");
	gettimeofday(&start,NULL);
	match_5(head,str,0);
	gettimeofday(&end,NULL);  //得到结束时间
	bm_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //计算经过的时间
	// printf("%f",timeuse/1000000.0);
	time_whole[4]+=bm_time;
	puts("");
	puts("");

	printf("%s","Shift-And\t| ");
	gettimeofday(&start,NULL);
	match_6(head->next,str,0);
	gettimeofday(&end,NULL);  //得到结束时间
	shift_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //计算经过的时间
	// printf("%f",timeuse/1000000.0);
	time_whole[5]+=shift_time;
	puts("");
	puts("");

	puts("time_use:");
	puts("algorithm\t|\ttime(s)");
	puts("-------------------------------------");
	printf("%s","Brute Force\t|\t");
	printf("%f\n",bf_time/1000000.0);

	printf("%s","KMP\t\t|\t");
	printf("%f\n",kmp_time/1000000.0);

	printf("%s","Horspool\t|\t");
	printf("%f\n",Horspool_time/1000000.0);

	printf("%s","Sunday\t\t|\t");
	printf("%f\n",Sunday_time/1000000.0);

	printf("%s", "BoyerMoore\t|\t");
	printf("%f\n",bm_time/1000000.0);

	printf("%s","Shift-And\t|\t");
	printf("%f\n",shift_time/1000000.0);
}

void showresult(int test_times){
	puts("average_time_use:");
	puts("algorithm\t|\ttime(s)");
	puts("-------------------------------------");
	printf("%s","Brute Force\t|\t");
	// printf("%d\n",time_whole[0] );
	time_whole[0]/=test_times;     				//xiaomeng
	printf("%f\n",time_whole[0]/1000000.0);

	printf("%s","KMP\t\t|\t");
	time_whole[1]/=test_times;
	printf("%f\n",time_whole[1]/1000000.0);

	printf("%s","Horspool\t|\t");
	time_whole[2]/=test_times;
	printf("%f\n",time_whole[2]/1000000.0);

	printf("%s","Sunday\t\t|\t");
	time_whole[3]/=test_times;
	printf("%f\n",time_whole[3]/1000000.0);

	printf("%s", "BoyerMoore\t|\t");
	time_whole[4]/=test_times;
	printf("%f\n",time_whole[4]/1000000.0);

	printf("%s","Shift-And\t|\t");
	time_whole[5]/=test_times;
	printf("%f\n",time_whole[5]/1000000.0);
}


/* name:Brute Force 
 * 没有依赖函数
 */

long match_1(node* head,char* str,long ppos){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);  //得到开始时间*/
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
			j=0;  //模式串回到第一个地府
			pos++;
			cur=pre->next;  //匹配串后退一个字符，继续进行比较
			pre=cur;  //保存当前位置
		}
			
	}
	if(j==strlength)
		printf("%d---",pos+ppos);
	if(cur->next!=NULL)
		match_1(cur,str,ppos+pos+strlength);
	else 
	 	printf("end of file!");
	/*gettimeofday(&end,NULL);  //得到结束时间
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;  //计算经过的时间
	printf("%f",timeuse/1000000.0);*/
}

void get_next(char* str,int* next){
	// puts(str);
	int i=1,j=0,k=0;
	next[1]=0;
	int strlength = strlen(str);//得到字符串的长度
	char str_2[strlength+2]; //需要依次后移一位，并且考虑结束符，所以长度是srelentgth+2
	while(str_2[k+1]=str[k]){  //依次后移
		// putchar(str[k]);
		k++;
	}
	while(i<strlength){
		if(j==0||str_2[i]==str_2[j]){
			i++;
			j++;
			next[i]=j;
			// printf("%d ",next[i]);
		}
		else 
			j=next[j];
	}  //得到next数组
}


/*
 *KMP算法
 *依赖函数：get_next();
*/
long match_2(node* head,char* str,long ppos){
	// puts(str);
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int i=0,j=1;
	long pos=0;  //记录累计移动的距离，加上传进来的参数ppos，就是模式串在匹配串中的位置
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	int next[strlength+1];
	
	get_next(str,next);  //得到next数组
	while(j<=strlength&&cur->next!=NULL){  //开始匹配
		if(j==0||str[j-1]==cur->ch){ 
			cur=cur->next;		//如果相等，模式串和匹配串同时后移，进行下一个字符的匹配
			pos++;
			j++;
		}
		else{
			j=next[j];  //如果不想等，就通过next数组得到此时匹配串的那个字符应该和模式串中的哪个进行匹配
		}
	}
	if(j>strlength)     //匹配成功则j>strlength,然后输出模式串在匹配串中的位置
		printf("%d---",pos+ppos-strlength);
	if(cur->next!=NULL)
		match_2(cur,str,pos+ppos);
	else 
		printf("end of file!");
	/*gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);*/
}

/*
 *movesteps()
 *移动链表指针，距离由参数传入
 *
*/
node* movesteps(node* head,int steps){
	int i;
	for(i=0;head!=NULL&&i<steps;i++){
		head=head->next;
	}
	return head;
}

/* name:Horspool 
 * 依赖函数：movesteps();
 */
long match_3(node* head,char* str,long ppos){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int  i=0,j,k;
	long pos=1;  
	node *cur;  
	char c;
	int strlength=strlen(str);
	//puts(str);
	if(strlength>1000){
		printf("  over length!");
		return;
	}
	//因为是从模式串的末尾开始匹配的，所以先将链表移动一个字符串长度的距离
	cur = movesteps(head,strlength);
	j=strlength-1;  //j指向字符串的最后一个字符
	while(j>=0&&cur!=NULL){
		if(str[j]==cur->ch){
			cur=cur->pre;
			i++;  //i记录字符匹配正确所移动的步数，便于其后如果出现不匹配字符的时候移动模式串
			j--;
		}
		else{
			c=cur->ch;
			while(j>=0&&str[j]!=c&&cur!=NULL){  //在模式串中寻找当前失配字符左边第一个与匹配串中的失配字符相同的字符的位置
				cur=cur->next;  //需要同时移动匹配串的指针使下一次能够正确地从模式串的末尾开始匹配
				pos++;  //记录移动的距离
				j--;
			}
			cur = movesteps(cur,i); //再移动已经匹配的距离，重新开始下一轮的匹配
			i=0;  //归零
			j=strlength-1;  //重新从末尾开始匹配
		}
	}
	//printf("%d\n",j );
	if(j<0)
		printf("%d---",pos+ppos);  //匹配成功
	if(cur!=NULL){
		cur=movesteps(cur,strlength);
		match_3(cur,str,pos+ppos+strlength-1);
	}
	else 
		printf("end of file!");
	/*gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);*/
	/* if(cur!=NULL)
		match_3(cur->next,str,pos+ppos);
	else 
		return; */
}

/* name:Sunday
 * 依赖函数movesteps();
 */

long match_4(node* head,char* str,long ppos){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int  i=0,j,k;
	long pos=1;  
	node *cur;  
	char c;
	int strlength=strlen(str);
	if(strlength>1000){
		printf("  over length!");
		return;
	}
	cur = movesteps(head,strlength);//从末尾开始匹配，所以先移动一个字符串的距离
	j=strlength-1;  //模式串从末尾开始匹配
	while(j>=0&&cur!=NULL){
		if(str[j]==cur->ch){
			cur=cur->pre;   //与Horspool一样
			i++;
			j--;
		}
		else{
			cur = movesteps(cur,i+1);  //出现失配时，匹配串后移一位，然后在模式串中寻找最右边与下一个字符相同的字符的位置
			pos++;  //距离计数加一
			i=0;
			if(cur==NULL)
				break;   //如果到末尾则退出
			j=strlength-1;
			while(j>=0&&str[j]!=cur->ch){
				j--;
			} //在模式串中寻找最右边与匹配串中下一个字符相同的字符的位置
			cur=movesteps(cur,strlength-j-1);
			pos=pos+strlength-j-1;  //距离计数
			j=strlength-1;  //重新从末尾开始匹配
		}
	}
	
	if(j<0)
		printf("%d---",pos+ppos);
	if(cur!=NULL){
		cur=movesteps(cur,strlength);	
		match_4(cur,str,pos+ppos+strlength-1);
	}
	else 
		printf("end of file!");
	/*gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);*/
	/* if(cur!=NULL)
		match_4(cur->next,str,pos+ppos);
	else
		return; */   //运用递归多次找出所有匹配的字符串
}

/*
 *BoyerMoore 坏字符数组
 *
*/
void get_bmbc(char* str,int* bmbc){
	int i;
	char c;
	int strlength = strlen(str);
	for(i=0;i<128;i++){
		bmbc[i]=strlength;
	}  //模式串中不存在的字符，移动距离为一个字符串的长度
	for(i=0;i<strlength;i++){
		c=str[i];
		bmbc[c]=strlength-i;  //坏字符数组下标是字符，数值是模式串中最靠右的该字符到右端的距离
		// printf("[%c]%d\n", c,bmbc[c]);
	}
}

/*
 *BoyerMoore 好后缀数组
 *
*/
void get_bmgs(char* str,int* bmgs){
	int i,j,p;
	int strlength = strlen(str);
	int suff[strlength];  //需要辅助数组suff[]，suff[]为以i为右边界, 与模式串后缀匹配的最大长度
	suff[strlength-1]=strlength;   //最后一个字符显然suff[]=strlength
	for(i=strlength-2;i>=0;i--){
		p=i;
		while(p>=0&&str[p]==str[strlength-1-i+p]){
			p--;
		}
		suff[i]=i-p;  //得到suff[]
	}
	// puts("suff:");
	/*for(i=0;i<strlength;i++){
		printf("suff[%d]%d\n", i,suff[i]);
	}*/
	//计算bmgs[]
	// puts("bmgs:");
	for(j=0;j<strlength;j++){
		bmgs[j]=strlength-1;		
	}  //没有匹配的好后缀时，移动的距离为strlength-1
	for(j=0;j<strlength-1;j++){
		bmgs[strlength-1-suff[j]]=strlength-1-j;	//得到bmgs[];	
		//printf("[%d]%d\n",strlength-1-suff[j],strlength-1-j );
	}
}

/*
 *BoyerMoore 依赖函数
 *比较好后缀与坏字符数组的大小，返回较大的那个数
*/
int max(int a,int b){
	return a>b?a:b;
}

/*
 *BoyerMoore 算法
 *依赖函数：get_bmgs(),get_bmbc(),max();
 *movesteps();
 */
long match_5(node* head,char* str,long ppos){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int  i=0,j,k;
	long pos=1;  //从当前位置开始计数，然后加上传进来的起始位置ppos
	node *cur; 
	char c;
	int strlength=strlen(str);
	int bmbc[128];  
	int bmgs[strlength];
	get_bmbc(str,bmbc);   //得到好后缀数组
	get_bmgs(str,bmgs);   //得到坏字符数组
	/*for(i=0;i<strlength;i++){
		printf("%c%d ",str[i],bmbc[str[i]] );
	}
	puts(" ");
	for(i=0;i<strlength;i++){
		printf("%3d",bmgs[i] );
	}*/

	//从后往前匹配，所以先往后移动一个模式串的长度
	cur = movesteps(head,strlength);
	if(cur==NULL){
		printf("end of file!");	
		return;  //如果已经到末尾了，则退出
	}
	j=strlength-1;  //最后一个字符
	while(j>=0){
		if(str[j]==cur->ch){
			cur=cur->pre;  //如果匹配则继续往前匹配前一个字符
			i++;
			j--;
		}
		else{
			c=cur->ch;   //不匹配时
			i+=max(bmbc[str[j]],bmgs[j]); //得到移动距离，为好后缀与坏字符数组中较大的那个，并加上先前已经匹配的那段距离i
			pos+=max(bmbc[str[j]],bmgs[j]);  //距离计数，不需要加上i
			cur=movesteps(cur,i);		///移动匹配串
			if(cur==NULL){
				printf("end of file!");
				break;
			}
			// putchar(cur->ch);
			i=0;		//归零
			j=strlength-1; //重新从末尾开始匹配
		}
	}
	if(j<0)
		printf("%d---",pos+ppos);
	if(cur!=NULL){
		cur=movesteps(cur,strlength);	
		match_5(cur,str,pos+ppos+strlength-1);
	}
	/*else 
		printf("end of file! / ");*/
	/*gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);*/
		//printf("find");
}




void get_b(char* str,int* B){
	int i,j;
	unsigned int shift=1;
	int strlength=strlen(str);
	for(i=0;i<strlength;i++){
		B[str[i]]|=shift;
		shift<<=1;
	}  //得到模式串中各个字符在模式串中的位置，由一个32位的二进制数来表示，存在的位置为1，不存在为0
	/*
	for(i=0;i<strlength;i++){
		printf("%c%x\n",str[i],B[str[i]]);
	}*/
}

/* name:Shift-And
 * 依赖函数：get_b();
 */
long match_6(node* head,char* str,long ppos){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int i;
	int B[128]={0};  //初始值为0
	long pos=1;
	int strlength=strlen(str);
	if(strlength>32){		//因为使用long类型来保存D，mask，所以最大的匹配长度为32位
		printf("  over length!");
		return;
	}
	long D=0,mask;
	mask = 1<<(strlength-1);  //得到标尺，当D与之相等的时候则匹配成功
	node* cur=head;
	get_b(str,B);		//得到辅助数组B
	while(cur!=NULL){
		D=(D<<1|1)&B[cur->ch];  //依次往后移动模式串，并更新D的数值
		cur=cur->next;
		pos++;
		if(D&mask)		//当D和mask相等的时候，说明匹配成功
			break;
	}
	if(D&mask)
		printf("%d---",pos+ppos-strlength);
	if(cur!=NULL)
		match_6(cur,str,pos+ppos-1);
	else 
		printf("end of file!");
	/*gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);*/
	/* if(cur!=NULL)
		match_6(cur,str,pos+ppos);
	else 
		return;
	 */  //通过递归寻找所有匹配的字符串
}