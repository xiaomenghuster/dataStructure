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

long match_1(node* head,char* str);  //匹配算法函数，传入需要匹配的字符串
void match_2(char* chp);
void match_3(char* chp);
void match_4(char* chp);
