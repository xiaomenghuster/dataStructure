#define CONTENTFILE   "ascii.txt"
#define ERROR  -1
#define TRUE 1
#define FALSE 0

typedef struct node{
	char ch;
	struct node *next;
	struct node *pre;
}node;  //保存文档中字符的结构

struct timeval{  
  long sec;
  long usec;
}; //计时


void start();  
int init(node*);  //初始化，将文件中的字符串读取到链表中
void getstring(long place,int strlength,char* str);
void show(node*);  //测试是否初始化成功
void create(int choice,long number); //ascii.c中产生数据文件
void display(node* head,char* str);  //调用匹配函数并显示匹配结果
void showresult(int test_times);  //显示最终的平均时间

long match_1(node* head,char* str,long ppos);  //Brute Force匹配算法函数，传入需要匹配的字符串
long match_2(node* head,char* str,long ppos);  //KMP 
	void get_next(char* , int*);//
long match_3(node* head,char* str,long ppos);  //Horspool
	node* movesteps(node *head,int steps);
long match_4(node* head,char* str,long ppos);  //Sunday
long match_5(node* head,char* str,long ppos);  //BoyerMoore
	void get_bmgs(char*,int*);
	void get_bmbc(char*,int*);
	int max(int ,int ); //返回较大的那个数
long match_6(node* head,char* str,long ppos);  //Shift-And
	void get_b(char*,int*);  //得到辅助数组
