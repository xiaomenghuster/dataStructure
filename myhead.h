#define CONTENTFILE   "ascii.txt"
#define ERROR  -1
#define TRUE 1
#define FALSE 0
typedef struct node{
	char ch;
	struct node *next;
	struct node *pre;
}node;
//计时 
struct timeval{  
  long sec;
  long usec;
};


void start();  
int init(node*);  //初始化，将文件中的字符串读取到链表中
void show(node*);  //测试是否初始化成功
void create(int choice,long number); //产生数据文件
void display(node* head,char* str);  //显示匹配结果

long match_1(node* head,char* str,long ppos);  //匹配算法函数，传入需要匹配的字符串
long match_2(node* head,char* str,long ppos);
	void get_next(char* , int*);//
long match_3(node* head,char* str,long ppos);
	node* movesteps(node *head,int steps);
long match_4(node* head,char* str,long ppos);
long match_5(node* head,char* str,long ppos);
	void get_bmgs(char*,int*);
	void get_bmbc(char*,int*);
long match_6(node* head,char* str,long ppos);
	void get_b(char*,long long*);
