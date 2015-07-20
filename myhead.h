#define CONTENTFILE   "ascii.txt"
#define ERROR  -1
typedef struct node{
	char ch;
	struct node *next;
}node;
void start();  
int init(node*);  //初始化，将文件中的字符串读取到链表中
void show(node*);  //测试是否初始化成功
void create(long number); //产生数据文件

long match_1(node* head,char* str,long ppos);  //匹配算法函数，传入需要匹配的字符串
long match_2(node* head,char* str,long ppos);
	void get_next(char* , int*);//
long match_3(node* head,char* str);
long match_4(node* head,char* str);
