#include <stdio.h>
#include  <stdlib.h>
#include <string.h>

//创建结构体及其成员 
typedef struct Node
{
 int number;//编号  
 char name[50];//书名
 char author[50];//作者
 char category[50];//种类 
 char publish[50];//出版社 
 struct Node *next;//指针
}book;

void create(book**head,int n1);//创建图书函数
void insert(book**head);//添加新图书函数 
void print(book**head);//输出所有图书信息函数 
void search1(book**head);//按照编号查询图书函数
void search2(book**head);//按照书名查询图书函数
void search3(book**head);//按照出版社查询
void search4(book**head);//按照图书种类查询 

int main()
{
	 char m,n; 
	 book*h = NULL;
	 book**Head=(book **)malloc(sizeof(h)) ;
 while(1)
 {
 printf("\n\n");
 printf("\t\t               欢迎使用图书管理系统   \n");
 printf("\t\t|---------------------------------------------------|\n");
 printf("\t\t|      1.创建图书信息(清除原来所有信息并新建）      |\n");
 printf("\t\t|      2.查找图书                                   |\n");
 printf("\t\t|      3.添加新书                                   |\n");
 printf("\t\t|      4.输出所有图书信息                           |\n");
 printf("\t\t|      5.退出系统                                   |\n");
 printf("\t\t|---------------------------------------------------|\n");
 printf("请输入您选择的操作对应的数字:");
 scanf("%s",&m);
 int a; 
 switch(m)
	{
		case'1':
		 printf("请输入您要创建信息的图书本数：") ;
		 scanf("%d",&n);
         create(Head,n);
         printf("\n"); 
         break;
        case '2':
        	printf("\t\t*********查询图书************\n");
			printf("\t\t     1.通过图书编号查询\n ");
			printf("\t\t     2.通过书名查询\n");
			printf("\t\t     3.通过出版社查询\n");
			printf("\t\t     4.通过图书种类查询\n"); 
			scanf("%d",&a);
			if(a==1)
			{ 
			search1(Head);
			break;
			}	
			if(a==2)
			{
			
				search2(Head);
				break;
			}	
			if(a==3)
			{
			search3(Head);
				break;
			}	
			if(a==4)
			{
			
			search4(Head);
				break;
			}
			break;	
			case '3':
				insert(Head);
				break;
			case '4':
				print(Head);
				break;
			case '5':
				printf("********************************正在退出************************************\n");
          		return 0;
          	default :
          		printf("输入有误，正在返回主菜单");
				break; 
	}
}
}
void create(book**head,int n1)
{
int num;
 book *p, *q,*l;//定义指针 
 *head = (book *)malloc(sizeof(book));//头节点开辟空间 
 l = *head;
 l->next = NULL;//置空头节点的指针域 
 q = l;//q指针记录头节点的地址 
 p = l->next;//p指针记录头节点的指针域的地址 
 int i =1;
 while(i<=n1)
 {
 	printf("请输入第%d本图书的编号：",i);
	scanf("%d", &num);
	book*p1 = p;
	while (p1!= NULL)
	{
		
		if (p1->number == num)
		{
		printf("编号不能重复，请重新输入：");//重复编号判定 
		scanf("%d",&num) ;
		p1 = l;
		}
		p1 = p1->next;
	}
	
  p = (book *)malloc(sizeof(book));//p指针开辟空间 
  p->number = num;
  printf("书名："); 
  scanf("%s",p->name);
  printf("作者：");
  scanf("%s",p->author);
  printf("出版社：");
  scanf("%s",p->publish);
  printf("种类：（科学技术 语言文学 政治经济 历史地理 艺术）");
  scanf("%s",p->category);
  p->next = NULL;//置空p节点的指针域  
  q->next = p;//p，q节点连接 
  q = p;//q指针后移
  i++;
 }
  printf("创建成功，正在返回主菜单");
 return ;
 
}
void search1(book**head)
{
 book*p,*l;//定义指针 
 l = *head;
 int num2,flag=0;//定义num2用于输入查找书籍 
 printf("请输入书编号:");
 //输入查找编号
 scanf("%d", &num2);
 p = l->next;
 while (p != NULL)
 {
  if (p->number==num2)//判断是否找到书籍
  {
   //为真时，输出信息 
     printf("****************书籍信息******************\n");
   printf(" 编号:%d\n",p->number);
   printf(" 书名:%s\n",p->name);     
   printf(" 作者:%s\n",p->author);
   printf(" 出版社:%s\n",p->publish);
   printf(" 种类:%s\n",p->category);
   flag=1;
    p = p->next;
  }
  else
   //为假时 
   p = p->next;//指针后移 
 }
 if (flag == 0)
  printf("该书不存在\n");
  printf("-----正在返回主菜单------") ;
}

void search2(book**head)
{
 book *p,*l;//定义指针
 l = *head; 
char name1[50];//定义name1用于输入查找书名 
int flag = 0;
 printf("请输入书名：");
 //输入查找书名 
 scanf("%s", name1);
 p = l->next;
 while (p != NULL)
 {
  if (strcmp( p->name, name1)==0)//判断是否找到书籍 
  {
   //为真时，输出信息 
   printf("****************书籍信息******************\n");
   printf(" 编号:%d\n",p->number);
   printf(" 书名:%s\n",p->name);     
   printf(" 作者:%s\n",p->author);
   printf(" 出版社:%s\n",p->publish);
   printf(" 种类:%s\n",p->category);
    flag =1;
    p = p->next;
  }
  else
   //为假时 
   p = p->next;//指针后移 
 }
 if (flag==0)//查找到最后一个节点还未查到要的编号时，输出ERROR INPUT
  printf("该书不存在\n");
    printf("-----正在返回主菜单------") ;
}
void search3(book**head)
{

 book *p,*l;//定义指针
 l = *head;  
 int flag =0;
char publish2[50];
 printf("请输入书的出版社:");
 //输入查找编号
 scanf("%s", &publish2);
 p = l->next;
 while (p != NULL)
 {
  if (strcmp( p->publish, publish2)==0)//判断是否找到书籍
  {
   //为真时，输出信息 
     printf("****************书籍信息******************\n");
   printf(" 编号:%d\n",p->number);
   printf(" 书名:%s\n",p->name);     
   printf(" 作者:%s\n",p->author);
   printf(" 出版社:%s\n",p->publish);
   printf(" 种类:%s\n",p->category);
    flag =1;
    p = p->next;
  }
  else
   //为假时 
   p = p->next;//指针后移 
 }
 if (flag == 0)
  printf("该书不存在\n");
	printf("-----正在返回主菜单------") ;
}
void search4(book **head)
{
 book *p,*l;//定义指针
 l = *head; 
 int flag =0; 
char category2[50];
 printf("请输入书的种类:");
 //输入查找编号
 scanf("%s", &category2);
 p = l->next;
 while (p != NULL)
 {
  if (strcmp( p->category, category2)==0)//判断是否找到书籍
  {
   //为真时，输出信息 
   printf("****************书籍信息******************\n");
   printf(" 编号:%d\n",p->number);
   printf(" 书名:%s\n",p->name);     
   printf(" 作者:%s\n",p->author);
   printf(" 出版社:%s\n",p->publish);
   printf(" 种类:%s\n",p->category);
 	flag = 1;
 	p = p->next;
  }
  else
   //为假时 
   p = p->next;//指针后移 
 }
 if (flag == 0)
  printf("该书不存在\n");
    printf("-----正在返回主菜单------") ;
}
void insert(book **head)
{
 int i, num;
 book *p, *r,*l; 
 l =*head;
 printf("请输入新增图书数量：");
 scanf("%d", &num);
for( i= 1;i<=num;i++) 
 {
 int num4; 
  r = (book*)malloc(sizeof(book));//为r开辟空间 
  r->next = NULL;//置空r的指针域 
 	printf("请输入新增加的第%d本图书的编号：",i);
 	scanf("%d", &num4);
 	book*p2 = l->next;
	while (p2!= NULL)
	{
		
		if (p2->number == num4)
		{
		printf("编号不能重复，请重新输入：");//重复编号判定 
		scanf("%d",&num4) ;
		p2 = l;
		}
		p2 = p2->next;
	}
	r->number = num4;
  printf("书名："); 
  scanf("%s",r->name);
  printf("作者：");
  scanf("%s",r->author);
  printf("出版社：");
  scanf("%s",r->publish);
  printf("种类：（科学技术 语言文学 政治经济 历史地理 艺术）");
  scanf("%s",r->category);
  p = l;
 if (p->next == NULL)
  {
   
    p->next = r;//连接节点 
    r->next = NULL;//置空r指针域
  }
 else
  {
   r->next = p->next;
   p->next = r;
   //实现将r节点插入链表 
  }
 
 }
   printf("增加图书信息成功，正在返回主菜单") ;
}
void print(book**head)
{
	book*l = *head;
	book*p = l->next;
	if(p==NULL)
	{
	printf("没有图书！请先创建");
	return;
	}
do{

	printf("****************书籍信息******************\n");
   printf(" 编号:%d\n",p->number);
   printf(" 书名:%s\n",p->name);     
   printf(" 作者:%s\n",p->author);
   printf(" 出版社:%s\n",p->publish);
   printf(" 种类:%s\n",p->category);
   p = p->next;
}while(p!=NULL);


}

