/*writor:xiaomenghuster  date:summer
 *���ݽṹ�γ����
 *�����ַ���ƥ���㷨
 *Ѱ������ƥ����ַ���λ�ã�û�������no find!
 *shift and ֻ��Ѱ��32���ַ����ڵ��ַ��������������Ϊ1000
*/
#include <stdio.h>
#include "myhead.h"
#include<stdlib.h>
#include<string.h>
#include<time.h>
long time_whole[6];  //��ʱ�� bf,kmp,horspool,sunday,bm,shift

int findall=0;
long place;

int main(){
	int i;
	for(i=0;i<6;i++)
		time_whole[i]=0;  //��¼�ۼ�ʱ����������
	cost *cost_head,*cost_p,*temp;
	cost_head=(cost*)malloc(sizeof(cost));
	cost_p=(cost*)malloc(sizeof(cost));
	cost_head->next=cost_p;  //����ʱ�������
	char str[1000];  //�����Դ���1000���ַ�����������Shift-And�㷨���ֻ�ܴ���32���ַ�
	int strlength,test_times,test_times_save,steps,steps_save,choice,iof,num_node;
	long number,distance;
	node *head,*p;
	start();  //���ϵͳ������Ϣ
	
	showiof();  //�����ʾ��Ϣ�����ֲ������͡�
	scanf("%d",&iof); 
	switch(iof){
		case 1:  
			/*show_asciikind();  //�����ʾ��Ϣ�������ɺ����ַ��ļ����͡�
			printf("your choice: ");
			scanf("%d",&choice);*/

			choice=1;

			puts("How many character do you want to produce?");  //���������ļ��Ĵ�С
			scanf("%d",&number);

			puts("please input the number of node and the strlength:");  //��ҪѰ�ҵĽ�����Լ��ַ�������
			scanf("%d %d",&num_node,&strlength);
			distance=number/num_node;  //���㲽��

		    puts("please input the test times:");   //����ÿ��λ����Ҫ���ԵĴ���
			scanf("%d",&test_times);
			test_times_save=test_times;   //����test_times����ֵ

			/*show_findall(); //�����Ѱ�ҵ�һ������Ѱ��ȫ��
			scanf("%d",&findall);*/

			while(num_node>0){
				place=number-(num_node-1)*distance-strlength; //�õ�ָ��λ��
				temp=(cost*)malloc(sizeof(cost));
				temp->next=NULL;
				temp->effective=1;
				temp->place=place;
				while(test_times_save>0){   //ʹ��test_time_save����test_time����ֵ
					create(choice,number);  //�γ��ַ����ļ�
					getstring(place,strlength,str);  //�õ�Ŀ���ַ���
					puts("\nthe string: ");
					puts(str);   //��ʾ�ַ���
					if(!(head=(node*)malloc(sizeof(node))))
						return ERROR;
					init(head);			//��ʼ��˫������ 
					display(head,str,findall,temp);  //����ƥ�亯����������
					puts("");
					test_times_save--;
				}
				showresult(test_times,temp);
				cost_p->next=temp;
				cost_p=temp;
				for(i=0;i<6;i++)
					time_whole[i]=0;  //���¹���
				num_node--;
				test_times_save=test_times;
			}
			//���н�������ӡ�����㷨�Ը���λ���ַ���ƥ��ɹ������ѵ�ʱ��
			puts("");
			puts("the time:");
			puts("\tbf\t   kmp\t      horspool\t sunday\t     bm\t\tshift");   
			cost_p=cost_head->next->next; 
			int j=1;
			while(cost_p!=NULL){
				//����һ��ʾ��ȷ����ָ��λ���ҵ����ַ���������������֮ǰ��λ���ҵ���
				printf("%d. ", j);
				if(cost_p->effective==1){
					printf("\t%f   ",cost_p->time_bf/1000000.0 );
					printf("%f   ",cost_p->time_kmp/1000000.0 );
					printf("%f   ",cost_p->time_horspool/1000000.0 );
					printf("%f   ",cost_p->time_sunday/1000000.0 );
					printf("%f   ",cost_p->time_bm/1000000.0 );
					printf("%f   ",cost_p->time_shift/1000000.0 );
					puts("");
				}
				else 
					puts("\tnone effective!");
				//printf("%d\n",cost_p->place );  //����Ƿ�ɹ���������
				j++;
				cost_p=cost_p->next;	
				// printf("%d\n",cost_p->effective_bf );
			}
			break;
		case 2:      //������������µ�ʱ��
			/*puts("please input the string:");
			scanf("%s",str);*/
			// test_times=1;
			/*show_findall();
			scanf("%d",&findall);*/
			puts("How many character do you want to produce?");  //���������ļ��Ĵ�С
			scanf("%d",&number);

			puts("the default strlength is 30");
			strlength=30;

		    puts("please input the steps:");   //����ÿ��λ����Ҫ���ԵĴ���
			scanf("%d",&steps);
			steps_save=steps;   //����test_times����ֵ

			show_asciikind();  //�����ʾ��Ϣ����Ҫ����ʲô�㷨���������
			scanf("%d",&choice);

			switch(choice){
				case 2:  //bf�㷨���������
					while(steps>0){   
						place=number-strlength;

						temp=(cost*)malloc(sizeof(cost));
						temp->next=NULL;
						temp->effective=1;
						temp->place=place;      //����һ�������¼��Ϣ

						create(choice,number);  //�γ��ַ����ļ�
						getstring(place,strlength,str);  //�õ�Ŀ���ַ���
						puts("\nthe string: ");
						puts(str);   //��ʾ�ַ���

						if(!(head=(node*)malloc(sizeof(node))))
							return ERROR;
						init(head);			//��ʼ��˫������ 
						display(head,str,findall,temp);  //����ƥ�亯��
						puts("");
						showresult(1,temp);
						cost_p->next=temp;
						cost_p=temp;
						for(i=0;i<6;i++)
							time_whole[i]=0;  //���¹���
						steps--;
						strlength+=10;
					}
					break;
				case 3:   //kmp��bm�㷨���������
					steps=4;  //�̶�ִ���ĴΣ����ĸ���ͬ�ļ�������ƥ�� �㷨��ʱ��
					while(steps>0){   
						place=number-strlength;

						temp=(cost*)malloc(sizeof(cost));
						temp->next=NULL;
						temp->effective=1;
						temp->place=place;      //����һ�������¼��Ϣ
						create_kmp(choice,number,steps,strlength);  //�γ��ַ����ļ�
						getstring(place,strlength,str);  //�õ�Ŀ���ַ���
						puts("\nthe string: ");
						puts(str);   //��ʾ�ַ���

						if(!(head=(node*)malloc(sizeof(node))))
							return ERROR;
						init(head);			//��ʼ��˫������ 
						display(head,str,findall,temp);  //����ƥ�亯��
						puts("");
						showresult(1,temp);
						cost_p->next=temp;
						cost_p=temp;
						for(i=0;i<6;i++)
							time_whole[i]=0;  //���¹���
						//���н�������ӡ���ѵ�ʱ��
						steps--;
						// strlength+=10;
					}
					break;
				case 4:  //horspool��sunday���������
					steps=4;
					while(steps>0){   
						place=number-strlength;

						temp=(cost*)malloc(sizeof(cost));
						temp->next=NULL;
						temp->effective=1;
						temp->place=place;      //����һ�������¼��Ϣ
						create_kmp(choice,number,steps,strlength);  //�γ��ַ����ļ�
						getstring(place,strlength,str);  //�õ�Ŀ���ַ���
						puts("\nthe string: ");
						puts(str);   //��ʾ�ַ���

						if(!(head=(node*)malloc(sizeof(node))))
							return ERROR;
						init(head);			//��ʼ��˫������ 
						display(head,str,findall,temp);  //����ƥ�亯��
						puts("");
						showresult(1,temp);
						cost_p->next=temp;
						cost_p=temp;
						for(i=0;i<6;i++)
							time_whole[i]=0;  //���¹���
						//���н�������ӡ���ѵ�ʱ��
						steps--;
						// strlength+=10;
					}
					break;
				case 5:  //shift���������
					steps=4;
					while(steps>0){   
						place=number-strlength;

						temp=(cost*)malloc(sizeof(cost));
						temp->next=NULL;
						temp->effective=1;
						temp->place=place;      //����һ�������¼��Ϣ
						create_kmp(choice,number,steps,strlength);  //�γ��ַ����ļ�
						getstring(place,strlength,str);  //�õ�Ŀ���ַ���
						puts("\nthe string: ");
						puts(str);   //��ʾ�ַ���

						if(!(head=(node*)malloc(sizeof(node))))
							return ERROR;
						init(head);			//��ʼ��˫������ 
						display(head,str,findall,temp);  //����ƥ�亯��
						puts("");
						showresult(1,temp);
						cost_p->next=temp;
						cost_p=temp;
						for(i=0;i<6;i++)
							time_whole[i]=0;  //���¹���
						//���н�������ӡ���ѵ�ʱ��
						steps--;
						// strlength+=10;
					}
					break;
				default: break;

			}
			
			//���н�������ӡ���ѵ�ʱ��
			puts("");
			puts("the time:");
			puts("�㷨����������ĶԱȣ�");   
			cost_p=cost_head->next->next; 
			while(cost_p!=NULL){
				//����һ��ʾ��ȷ����ָ��λ���ҵ����ַ���������������֮ǰ��λ���ҵ���
				if(cost_p->effective==1){
					switch(choice){
						case 2: printf("\tkmp:%f   ",cost_p->time_bf/1000000.0 );break;
						case 3: 
							printf("\tkmp:%f   bm:%f",cost_p->time_kmp/1000000.0,cost_p->time_bm/1000000.0 );break;
						case 4: printf("\thorspool:%f   sunday:%f",cost_p->time_horspool/1000000.0,cost_p->time_sunday );break;
						case 5: printf("\tshift:%f   ",cost_p->time_shift/1000000.0 );break;
						default: break;
					}
					puts("");
				}
				else 
					puts("\tnone effective!");
				//printf("%d\n",cost_p->place );  //����Ƿ�ɹ���������
				j++;
				cost_p=cost_p->next;	
				// printf("%d\n",cost_p->effective_bf );
			}
			break;
		default: break;
	}

	
	
}

void start(){
	printf(" ------------------------------------------\n");
	printf("| This the string-match algorithm!         |\n");
	printf("| Auther:xiaomeng                          |\n");
	printf("| Date:2015.9.21                           |\n");
	printf("|-----------all right reserve--------------|\n");
	puts("");
}

void showiof(){
	printf("-------------------------------------------------------\n");
	printf("|  ѡ���������:                                      |\n");
	printf("| 1:�Զ�ѡ����Բ�ͬλ��ƥ���ٶ�  2:�����������  |\n"); 
	printf("-------------------------------------------------------\n");
}

void show_asciikind(){
	printf("----------------------------------------------------------\n");
	printf("|  ����ʲôƥ���㷨�����������                      |\n");
	printf("| 2:Brute Force  3:KMP/BM  4:Horspool/Sunday 5:Shift-And |\n"); 
	printf("----------------------------------------------------------\n");
}

void show_findall(){
	printf("---------------\n");
	printf("|  find all?  |\n");
	printf("| 1:yes  0:no |\n"); 
	printf("---------------\n");
}

void create(int choice,long number){
	char c;
	int kind;
	long i=0;
	FILE* fout= fopen(CONTENTFILE,"w");
	while(i<number){
		switch(choice){
			case 1:
				c=(rand()%9)%2+'0';   //���������01�ļ�������α�����01�ļ�
				//putchar(c);
				fputc(c,fout);
				break;
			case 2:
				c='a';  //���ɴ����ظ����ַ�������ƥ������Ҫ��ʱ��
				if(i==number-2)
					c='b';
				// putchar(c);
				fputc(c,fout);
				break;
			case 3:
				c=rand()%93+33;  //�������ascii���п�����ʾ�������ַ�
				// putchar(c);
				fputc(c,fout);
				if(i==number-2)
					c='d';
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
			case 5:
				c=rand()%93+33;  //�������ascii���п�����ʾ�������ַ�
				// putchar(c);
				fputc(c,fout);
				break;
			default:
				break;
		}
		/*if(!(i%10000))
			fputc('\n',fout);*/
		i++;
	}
	fclose(fout);
}

void create_kmp(int choice,long number,int steps,int strlength){
	char c='a';
	int kind;
	long i=0;
	FILE* fout= fopen(CONTENTFILE,"w");
	while(i<number){
		switch(steps){
			case 1:
				c=(rand()%9)%2+'0';   //���������01�ļ�������α�����01�ļ�
				//putchar(c);
				fputc(c,fout);
				break;
			case 2:
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
					default: break;
				}
				fputc(c,fout);
				break;
			case 3:
				c=rand()%26+'a';  //�������ascii���п�����ʾ�������ַ�
				// putchar(c);
				fputc(c,fout);
				break;
			case 4:
				if(c=='e')
					c='a';
				fputc(c,fout);
				c++;
				break;
			default:
				break;
		}
		i++;
		if(i==number-2){
			c='/';
			fputc(c,fout);
		}
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
		p->pre=h;  //����ƥ���㷨��Ҫ˫������
		h=p;
		//putchar(c);
	}
	h->next=NULL;
} 

void show(node* h){   //��ʾ˫�����������������
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

void display(node* head,char* str,int findall,cost *cost_p){
	struct timeval start,end;
	long bf_time,kmp_time,Horspool_time,Sunday_time,bm_time,shift_time;
	puts("finding results:");
	
	printf("%s","Brute Force\t| ");
	gettimeofday(&start,NULL);  //�õ���ʼʱ��
	match_1(head,str,0,findall,cost_p);
	gettimeofday(&end,NULL);  //�õ�����ʱ��
	bf_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //���㾭����ʱ��
	//printf("%f",timeuse/1000000.0);
	time_whole[0]+=bf_time;  //ʱ���ۼ�
	puts("");					//����
	puts("");

	printf("%s","KMP\t\t| ");
	gettimeofday(&start,NULL);  //�õ���ʼʱ��
	match_2(head,str,0,findall);
	gettimeofday(&end,NULL);  //�õ�����ʱ��
	kmp_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //���㾭����ʱ��
	// printf("%f",timeuse/1000000.0);
	time_whole[1]+=kmp_time;
	puts("");
	puts("");					//����

	printf("%s","Horspool\t| ");
	gettimeofday(&start,NULL);
	match_3(head,str,0,findall);
	gettimeofday(&end,NULL);  //�õ�����ʱ��
	Horspool_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //���㾭����ʱ��
	// printf("%f",timeuse/1000000.0);
	time_whole[2]+=Horspool_time;
	puts("");
	puts("");

	printf("%s","Sunday\t\t| ");
	gettimeofday(&start,NULL);
	match_4(head,str,0,findall);
	gettimeofday(&end,NULL);  //�õ�����ʱ��
	Sunday_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //���㾭����ʱ��
	// printf("%f",timeuse/1000000.0);
	time_whole[3]+=Sunday_time;
	puts("");
	puts("");

	printf("%s", "BoyerMoore\t| ");
	gettimeofday(&start,NULL);
	match_5(head,str,0,findall);
	gettimeofday(&end,NULL);  //�õ�����ʱ��
	bm_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //���㾭����ʱ��
	// printf("%f",timeuse/1000000.0);
	time_whole[4]+=bm_time;
	puts("");
	puts("");

	printf("%s","Shift-And\t| ");
	gettimeofday(&start,NULL);
	match_6(head->next,str,0,findall);
	gettimeofday(&end,NULL);  //�õ�����ʱ��
	shift_time=1000000*(end.sec-start.sec)+end.usec-start.usec;  //���㾭����ʱ��
	// printf("%f",timeuse/1000000.0);
	time_whole[5]+=shift_time;
	puts("");
	puts("");

	//�ͷ��ڴ�ռ�
	node* head_save=(node*)malloc(sizeof(node));
	while(head!=NULL){
		head_save=head->next;
		free(head);
		head=head_save;
	}

	//����˴�ƥ��������ʱ��
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

void showresult(int test_times,cost *cost_p){
	puts("average_time_use:");
	puts("algorithm\t|\ttime(s)");
	puts("-------------------------------------");
	printf("%s","Brute Force\t|\t");
	// printf("%d\n",time_whole[0] );
	time_whole[0]/=test_times;     				//xiaomeng
	printf("%f\n",time_whole[0]/1000000.0);
	cost_p->time_bf=time_whole[0];


	printf("%s","KMP\t\t|\t");
	time_whole[1]/=test_times;
	printf("%f\n",time_whole[1]/1000000.0);
	cost_p->time_kmp=time_whole[1];

	printf("%s","Horspool\t|\t");
	time_whole[2]/=test_times;
	printf("%f\n",time_whole[2]/1000000.0);
	cost_p->time_horspool=time_whole[2];

	printf("%s","Sunday\t\t|\t");
	time_whole[3]/=test_times;
	printf("%f\n",time_whole[3]/1000000.0);
	cost_p->time_sunday=time_whole[3];

	printf("%s", "BoyerMoore\t|\t");
	time_whole[4]/=test_times;
	printf("%f\n",time_whole[4]/1000000.0);
	cost_p->time_bm=time_whole[4];

	printf("%s","Shift-And\t|\t");
	time_whole[5]/=test_times;
	printf("%f\n",time_whole[5]/1000000.0);
	cost_p->time_shift=time_whole[5];

	/*cost *temp;	
	temp=(cost*)malloc(sizeof(cost));  //���浱ǰλ��ƥ������ʱ���ƽ��ֵ��������λ�����Ƚ�
	temp->next=NULL;
	cost_p->next=temp;
	return temp;*/
}


/* name:Brute Force 
 * û����������
 */

long match_1(node* head,char* str,long ppos,int findall,cost *cost_p){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);  //�õ���ʼʱ��*/
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
			j=0;  //ģʽ���ص���һ���ظ�
			pos++;
			cur=pre->next;  //ƥ�䴮����һ���ַ����������бȽ�
			pre=cur;  //���浱ǰλ��
		}
			
	}
	if(j==strlength)
		printf("%d---",pos+ppos);
	printf("%d\n",place );
	if(place!=pos+ppos)
		cost_p->effective=0;
	//printf("%d\n",cost_p->effective );
	if(cur->next!=NULL&&findall)
		match_1(cur,str,ppos+pos+strlength,findall,cost_p);
	else if(findall) 
	 	printf("end of file!");
	/*gettimeofday(&end,NULL);  //�õ�����ʱ��
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;  //���㾭����ʱ��
	printf("%f",timeuse/1000000.0);*/
}

void get_next(char* str,int* next){
	// puts(str);
	int i=1,j=0,k=0;
	next[1]=0;
	int strlength = strlen(str);//�õ��ַ����ĳ���
	char str_2[strlength+2]; //��Ҫ���κ���һλ�����ҿ��ǽ����������Գ�����srelentgth+2
	while(str_2[k+1]=str[k]){  //���κ���
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
	}  //�õ�next����
}


/*
 *KMP�㷨
 *����������get_next();
*/
long match_2(node* head,char* str,long ppos,int findall){
	// puts(str);
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int i=0,j=1;
	long pos=0;  //��¼�ۼ��ƶ��ľ��룬���ϴ������Ĳ���ppos������ģʽ����ƥ�䴮�е�λ��
	node *cur,*pre;
	cur=head;
	pre=head;
	int strlength=strlen(str);
	int next[strlength+1];
	
	get_next(str,next);  //�õ�next����
	while(j<=strlength&&cur->next!=NULL){  //��ʼƥ��
		if(j==0||str[j-1]==cur->ch){ 
			cur=cur->next;		//�����ȣ�ģʽ����ƥ�䴮ͬʱ���ƣ�������һ���ַ���ƥ��
			pos++;
			j++;
		}
		else{
			j=next[j];  //�������ȣ���ͨ��next����õ���ʱƥ�䴮���Ǹ��ַ�Ӧ�ú�ģʽ���е��ĸ�����ƥ��
		}
	}
	if(j>strlength)     //ƥ��ɹ���j>strlength,Ȼ�����ģʽ����ƥ�䴮�е�λ��
		printf("%d---",pos+ppos-strlength);
	if(cur->next!=NULL&&findall)
		match_2(cur,str,pos+ppos,findall);
	else if(findall)
		printf("end of file!");
	/*gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);*/
}

/*
 *movesteps()
 *�ƶ�����ָ�룬�����ɲ�������
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
 * ����������movesteps();
 */
long match_3(node* head,char* str,long ppos,int findall){
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
	//��Ϊ�Ǵ�ģʽ����ĩβ��ʼƥ��ģ������Ƚ������ƶ�һ���ַ������ȵľ���
	cur = movesteps(head,strlength);
	j=strlength-1;  //jָ���ַ��������һ���ַ�
	while(j>=0&&cur!=NULL){
		if(str[j]==cur->ch){
			cur=cur->pre;
			i++;  //i��¼�ַ�ƥ����ȷ���ƶ��Ĳ������������������ֲ�ƥ���ַ���ʱ���ƶ�ģʽ��
			j--;
		}
		else{
			c=cur->ch;
			while(j>=0&&str[j]!=c&&cur!=NULL){  //��ģʽ����Ѱ�ҵ�ǰʧ���ַ���ߵ�һ����ƥ�䴮�е�ʧ���ַ���ͬ���ַ���λ��
				cur=cur->next;  //��Ҫͬʱ�ƶ�ƥ�䴮��ָ��ʹ��һ���ܹ���ȷ�ش�ģʽ����ĩβ��ʼƥ��
				pos++;  //��¼�ƶ��ľ���
				j--;
			}
			cur = movesteps(cur,i); //���ƶ��Ѿ�ƥ��ľ��룬���¿�ʼ��һ�ֵ�ƥ��
			i=0;  //����
			j=strlength-1;  //���´�ĩβ��ʼƥ��
		}
	}
	//printf("%d\n",j );
	if(j<0)
		printf("%d---",pos+ppos);  //ƥ��ɹ�
	if(cur!=NULL&&findall){
		cur=movesteps(cur,strlength);
		match_3(cur,str,pos+ppos+strlength-1,findall);
	}
	else if(findall)
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
 * ��������movesteps();
 */

/*long match_4(node* head,char* str,long ppos,int findall){
	//puts(str);
	int  i=0,j=0;
	long pos=1;  
	node *cur,*cur_save,*next;  
	char c;
	int strlength=strlen(str);
	//puts(str);
	// printf("%d\n",strlength);
	if(strlength>1000){
		printf("  over length!");
		return;
	}
	cur=(node*)malloc(sizeof(node));
	cur=head->next;
	next=(node*)malloc(sizeof(node));
	cur_save=(node*)malloc(sizeof(node));
	// putchar(cur->ch);
	while(j<strlength&&cur!=NULL){
		if(str[j]==cur->ch){
			cur=cur->next;  
			i++;
			j++;
			pos++;
		}
		else{
			cur_save=cur;
			next = movesteps(cur,strlength-i);  //����ʧ��ʱ��ƥ�䴮����һλ��Ȼ����ģʽ����Ѱ�����ұ�����һ���ַ���ͬ���ַ���λ��
			if(next==NULL){
				cur=NULL;
				break;   //�����ĩβ���˳�
			}
			j=strlength-1;
			while(j>=0&&str[j]!=next->ch){
				j--;
			} //��ģʽ����Ѱ�����ұ���ƥ�䴮����һ���ַ���ͬ���ַ���λ��
			cur=movesteps(cur_save,strlength-j); //���¶���Ȼ��ʼ��������ƥ��
			pos+=strlength-j;
			i=0;
			j=0;
		}
	}
	
	if(j==strlength)
		printf("%d---",pos+ppos-strlength);
	if(cur!=NULL&&findall){
		match_4(cur->pre->pre,str,pos+ppos-2,findall);
	}
	else if(findall)
		printf("end of file!");    //����ȫ��ƥ��ɹ�
}
*/
long match_4(node* head,char* str,long ppos,int findall){
	int  i=0,j,k;
	long pos=1;  
	node *cur;  
	char c;
	int strlength=strlen(str);
	if(strlength>1000){
		printf("  over length!");
		return;
	}
	cur = movesteps(head,strlength);//��ĩβ��ʼƥ�䣬�������ƶ�һ���ַ����ľ���
	j=strlength-1;  //ģʽ����ĩβ��ʼƥ��
	while(j>=0&&cur!=NULL){
		if(str[j]==cur->ch){
			cur=cur->pre;   //��Horspoolһ��
			i++;
			j--;
		}
		else{
			cur = movesteps(cur,i+1);  //����ʧ��ʱ��ƥ�䴮����һλ��Ȼ����ģʽ����Ѱ�����ұ�����һ���ַ���ͬ���ַ���λ��
			pos++;  //���������һ
			i=0;
			if(cur==NULL)
				break;   //�����ĩβ���˳�
			j=strlength-1;
			while(j>=0&&str[j]!=cur->ch){
				j--;
			} //��ģʽ����Ѱ�����ұ���ƥ�䴮����һ���ַ���ͬ���ַ���λ��
			cur=movesteps(cur,strlength-j-1);
			pos=pos+strlength-j-1;  //�������
			j=strlength-1;  //���´�ĩβ��ʼƥ��
		}
	}
	
	if(j<0)
		printf("%d---",pos+ppos);
	if(cur!=NULL&&findall){
		cur=movesteps(cur,strlength);	
		match_4(cur,str,pos+ppos+strlength-1,findall);
	}
	else if(findall)
		printf("end of file!");
}

/*
 *BoyerMoore ���ַ�����
 *
*/
void get_bmbc(char* str,int* bmbc){
	int i;
	char c;
	int strlength = strlen(str);
	for(i=0;i<128;i++){
		bmbc[i]=strlength;
	}  //ģʽ���в����ڵ��ַ����ƶ�����Ϊһ���ַ����ĳ���
	for(i=0;i<strlength;i++){
		c=str[i];
		bmbc[c]=strlength-i;  //���ַ������±����ַ�����ֵ��ģʽ������ҵĸ��ַ����Ҷ˵ľ���
		// printf("[%c]%d\n", c,bmbc[c]);
	}
}

/*
 *BoyerMoore �ú�׺����
 *
*/
void get_bmgs(char* str,int* bmgs){
	int i,j,p;
	int strlength = strlen(str);
	int suff[strlength];  //��Ҫ��������suff[]��suff[]Ϊ��iΪ�ұ߽�, ��ģʽ����׺ƥ�����󳤶�
	suff[strlength-1]=strlength;   //���һ���ַ���Ȼsuff[]=strlength
	for(i=strlength-2;i>=0;i--){
		p=i;
		while(p>=0&&str[p]==str[strlength-1-i+p]){
			p--;
		}
		suff[i]=i-p;  //�õ�suff[]
	}
	// puts("suff:");
	/*for(i=0;i<strlength;i++){
		printf("suff[%d]%d\n", i,suff[i]);
	}*/
	//����bmgs[]
	// puts("bmgs:");
	for(j=0;j<strlength;j++){
		bmgs[j]=strlength-1;		
	}  //û��ƥ��ĺú�׺ʱ���ƶ��ľ���Ϊstrlength-1
	for(j=0;j<strlength-1;j++){
		bmgs[strlength-1-suff[j]]=strlength-1-j;	//�õ�bmgs[];	
		//printf("[%d]%d\n",strlength-1-suff[j],strlength-1-j );
	}
}

/*
 *BoyerMoore ��������
 *�ȽϺú�׺�뻵�ַ�����Ĵ�С�����ؽϴ���Ǹ���
*/
int max(int a,int b){
	return a>b?a:b;
}

/*
 *BoyerMoore �㷨
 *����������get_bmgs(),get_bmbc(),max();
 *movesteps();
 */
long match_5(node* head,char* str,long ppos,int findall){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int  i=0,j,k;
	long pos=1;  //�ӵ�ǰλ�ÿ�ʼ������Ȼ����ϴ���������ʼλ��ppos
	node *cur; 
	char c;
	int strlength=strlen(str);
	int bmbc[128];  
	int bmgs[strlength];
	get_bmbc(str,bmbc);   //�õ��ú�׺����
	get_bmgs(str,bmgs);   //�õ����ַ�����
	/*for(i=0;i<strlength;i++){
		printf("%c%d ",str[i],bmbc[str[i]] );
	}
	puts(" ");
	for(i=0;i<strlength;i++){
		printf("%3d",bmgs[i] );
	}*/

	//�Ӻ���ǰƥ�䣬�����������ƶ�һ��ģʽ���ĳ���
	cur = movesteps(head,strlength);
	if(cur==NULL){
		printf("end of file!");	
		return;  //����Ѿ���ĩβ�ˣ����˳�
	}
	j=strlength-1;  //���һ���ַ�
	while(j>=0){
		if(str[j]==cur->ch){
			cur=cur->pre;  //���ƥ���������ǰƥ��ǰһ���ַ�
			i++;
			j--;
		}
		else{
			c=cur->ch;   //��ƥ��ʱ
			i+=max(bmbc[str[j]],bmgs[j]); //�õ��ƶ����룬Ϊ�ú�׺�뻵�ַ������нϴ���Ǹ�����������ǰ�Ѿ�ƥ����Ƕξ���i
			pos+=max(bmbc[str[j]],bmgs[j]);  //�������������Ҫ����i
			cur=movesteps(cur,i);		///�ƶ�ƥ�䴮
			if(cur==NULL){
				printf("end of file!");
				break;
			}
			// putchar(cur->ch);
			i=0;		//����
			j=strlength-1; //���´�ĩβ��ʼƥ��
		}
	}
	if(j<0)
		printf("%d---",pos+ppos);
	if(cur!=NULL&&findall){
		cur=movesteps(cur,strlength);	
		match_5(cur,str,pos+ppos+strlength-1,findall);
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
	}  //�õ�ģʽ���и����ַ���ģʽ���е�λ�ã���һ��32λ�Ķ�����������ʾ�����ڵ�λ��Ϊ1��������Ϊ0
	/*
	for(i=0;i<strlength;i++){
		printf("%c%x\n",str[i],B[str[i]]);
	}*/
}

/* name:Shift-And
 * ����������get_b();
 */
long match_6(node* head,char* str,long ppos,int findall){
	/*struct timeval start,end;
	gettimeofday(&start,NULL);*/
	int i;
	int B[128]={0};  //��ʼֵΪ0
	long pos=1;
	int strlength=strlen(str);
	if(strlength>32){		//��Ϊʹ��long����������D��mask����������ƥ�䳤��Ϊ32λ
		printf("  over length!");
		return;
	}
	long D=0,mask;
	mask = 1<<(strlength-1);  //�õ���ߣ���D��֮��ȵ�ʱ����ƥ��ɹ�
	node* cur=head;
	get_b(str,B);		//�õ���������B
	while(cur!=NULL){
		D=(D<<1|1)&B[cur->ch];  //���������ƶ�ģʽ����������D����ֵ
		cur=cur->next;
		pos++;
		if(D&mask)		//��D��mask��ȵ�ʱ��˵��ƥ��ɹ�
			break;
	}
	if(D&mask)
		printf("%d---",pos+ppos-strlength);
	if(cur!=NULL&&findall)
		match_6(cur,str,pos+ppos-1,findall);
	else if(findall)
		printf("end of file!");
	/*gettimeofday(&end,NULL);
	long timeuse=1000000*(end.sec-start.sec)+end.usec-start.usec;
	printf("%f",timeuse/1000000.0);*/
	/* if(cur!=NULL)
		match_6(cur,str,pos+ppos);
	else 
		return;
	 */  //ͨ���ݹ�Ѱ������ƥ����ַ���
}