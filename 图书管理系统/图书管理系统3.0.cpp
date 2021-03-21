#include <stdio.h>
#include  <stdlib.h>
#include <string.h>

//�����ṹ�弰���Ա 
typedef struct Node
{
 int number;//���  
 char name[50];//����
 char author[50];//����
 char category[50];//���� 
 char publish[50];//������ 
 struct Node *next;//ָ��
}book;

void create(book**head,int n1);//����ͼ�麯��
void insert(book**head);//�����ͼ�麯�� 
void print(book**head);//�������ͼ����Ϣ���� 
void search1(book**head);//���ձ�Ų�ѯͼ�麯��
void search2(book**head);//����������ѯͼ�麯��
void search3(book**head);//���ճ������ѯ
void search4(book**head);//����ͼ�������ѯ 

int main()
{
	 char m,n; 
	 book*h = NULL;
	 book**Head=(book **)malloc(sizeof(h)) ;
 while(1)
 {
 printf("\n\n");
 printf("\t\t               ��ӭʹ��ͼ�����ϵͳ   \n");
 printf("\t\t|---------------------------------------------------|\n");
 printf("\t\t|      1.����ͼ����Ϣ(���ԭ��������Ϣ���½���      |\n");
 printf("\t\t|      2.����ͼ��                                   |\n");
 printf("\t\t|      3.�������                                   |\n");
 printf("\t\t|      4.�������ͼ����Ϣ                           |\n");
 printf("\t\t|      5.�˳�ϵͳ                                   |\n");
 printf("\t\t|---------------------------------------------------|\n");
 printf("��������ѡ��Ĳ�����Ӧ������:");
 scanf("%s",&m);
 int a; 
 switch(m)
	{
		case'1':
		 printf("��������Ҫ������Ϣ��ͼ�鱾����") ;
		 scanf("%d",&n);
         create(Head,n);
         printf("\n"); 
         break;
        case '2':
        	printf("\t\t*********��ѯͼ��************\n");
			printf("\t\t     1.ͨ��ͼ���Ų�ѯ\n ");
			printf("\t\t     2.ͨ��������ѯ\n");
			printf("\t\t     3.ͨ���������ѯ\n");
			printf("\t\t     4.ͨ��ͼ�������ѯ\n"); 
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
				printf("********************************�����˳�************************************\n");
          		return 0;
          	default :
          		printf("�����������ڷ������˵�");
				break; 
	}
}
}
void create(book**head,int n1)
{
int num;
 book *p, *q,*l;//����ָ�� 
 *head = (book *)malloc(sizeof(book));//ͷ�ڵ㿪�ٿռ� 
 l = *head;
 l->next = NULL;//�ÿ�ͷ�ڵ��ָ���� 
 q = l;//qָ���¼ͷ�ڵ�ĵ�ַ 
 p = l->next;//pָ���¼ͷ�ڵ��ָ����ĵ�ַ 
 int i =1;
 while(i<=n1)
 {
 	printf("�������%d��ͼ��ı�ţ�",i);
	scanf("%d", &num);
	book*p1 = p;
	while (p1!= NULL)
	{
		
		if (p1->number == num)
		{
		printf("��Ų����ظ������������룺");//�ظ�����ж� 
		scanf("%d",&num) ;
		p1 = l;
		}
		p1 = p1->next;
	}
	
  p = (book *)malloc(sizeof(book));//pָ�뿪�ٿռ� 
  p->number = num;
  printf("������"); 
  scanf("%s",p->name);
  printf("���ߣ�");
  scanf("%s",p->author);
  printf("�����磺");
  scanf("%s",p->publish);
  printf("���ࣺ����ѧ���� ������ѧ ���ξ��� ��ʷ���� ������");
  scanf("%s",p->category);
  p->next = NULL;//�ÿ�p�ڵ��ָ����  
  q->next = p;//p��q�ڵ����� 
  q = p;//qָ�����
  i++;
 }
  printf("�����ɹ������ڷ������˵�");
 return ;
 
}
void search1(book**head)
{
 book*p,*l;//����ָ�� 
 l = *head;
 int num2,flag=0;//����num2������������鼮 
 printf("����������:");
 //������ұ��
 scanf("%d", &num2);
 p = l->next;
 while (p != NULL)
 {
  if (p->number==num2)//�ж��Ƿ��ҵ��鼮
  {
   //Ϊ��ʱ�������Ϣ 
     printf("****************�鼮��Ϣ******************\n");
   printf(" ���:%d\n",p->number);
   printf(" ����:%s\n",p->name);     
   printf(" ����:%s\n",p->author);
   printf(" ������:%s\n",p->publish);
   printf(" ����:%s\n",p->category);
   flag=1;
    p = p->next;
  }
  else
   //Ϊ��ʱ 
   p = p->next;//ָ����� 
 }
 if (flag == 0)
  printf("���鲻����\n");
  printf("-----���ڷ������˵�------") ;
}

void search2(book**head)
{
 book *p,*l;//����ָ��
 l = *head; 
char name1[50];//����name1��������������� 
int flag = 0;
 printf("������������");
 //����������� 
 scanf("%s", name1);
 p = l->next;
 while (p != NULL)
 {
  if (strcmp( p->name, name1)==0)//�ж��Ƿ��ҵ��鼮 
  {
   //Ϊ��ʱ�������Ϣ 
   printf("****************�鼮��Ϣ******************\n");
   printf(" ���:%d\n",p->number);
   printf(" ����:%s\n",p->name);     
   printf(" ����:%s\n",p->author);
   printf(" ������:%s\n",p->publish);
   printf(" ����:%s\n",p->category);
    flag =1;
    p = p->next;
  }
  else
   //Ϊ��ʱ 
   p = p->next;//ָ����� 
 }
 if (flag==0)//���ҵ����һ���ڵ㻹δ�鵽Ҫ�ı��ʱ�����ERROR INPUT
  printf("���鲻����\n");
    printf("-----���ڷ������˵�------") ;
}
void search3(book**head)
{

 book *p,*l;//����ָ��
 l = *head;  
 int flag =0;
char publish2[50];
 printf("��������ĳ�����:");
 //������ұ��
 scanf("%s", &publish2);
 p = l->next;
 while (p != NULL)
 {
  if (strcmp( p->publish, publish2)==0)//�ж��Ƿ��ҵ��鼮
  {
   //Ϊ��ʱ�������Ϣ 
     printf("****************�鼮��Ϣ******************\n");
   printf(" ���:%d\n",p->number);
   printf(" ����:%s\n",p->name);     
   printf(" ����:%s\n",p->author);
   printf(" ������:%s\n",p->publish);
   printf(" ����:%s\n",p->category);
    flag =1;
    p = p->next;
  }
  else
   //Ϊ��ʱ 
   p = p->next;//ָ����� 
 }
 if (flag == 0)
  printf("���鲻����\n");
	printf("-----���ڷ������˵�------") ;
}
void search4(book **head)
{
 book *p,*l;//����ָ��
 l = *head; 
 int flag =0; 
char category2[50];
 printf("�������������:");
 //������ұ��
 scanf("%s", &category2);
 p = l->next;
 while (p != NULL)
 {
  if (strcmp( p->category, category2)==0)//�ж��Ƿ��ҵ��鼮
  {
   //Ϊ��ʱ�������Ϣ 
   printf("****************�鼮��Ϣ******************\n");
   printf(" ���:%d\n",p->number);
   printf(" ����:%s\n",p->name);     
   printf(" ����:%s\n",p->author);
   printf(" ������:%s\n",p->publish);
   printf(" ����:%s\n",p->category);
 	flag = 1;
 	p = p->next;
  }
  else
   //Ϊ��ʱ 
   p = p->next;//ָ����� 
 }
 if (flag == 0)
  printf("���鲻����\n");
    printf("-----���ڷ������˵�------") ;
}
void insert(book **head)
{
 int i, num;
 book *p, *r,*l; 
 l =*head;
 printf("����������ͼ��������");
 scanf("%d", &num);
for( i= 1;i<=num;i++) 
 {
 int num4; 
  r = (book*)malloc(sizeof(book));//Ϊr���ٿռ� 
  r->next = NULL;//�ÿ�r��ָ���� 
 	printf("�����������ӵĵ�%d��ͼ��ı�ţ�",i);
 	scanf("%d", &num4);
 	book*p2 = l->next;
	while (p2!= NULL)
	{
		
		if (p2->number == num4)
		{
		printf("��Ų����ظ������������룺");//�ظ�����ж� 
		scanf("%d",&num4) ;
		p2 = l;
		}
		p2 = p2->next;
	}
	r->number = num4;
  printf("������"); 
  scanf("%s",r->name);
  printf("���ߣ�");
  scanf("%s",r->author);
  printf("�����磺");
  scanf("%s",r->publish);
  printf("���ࣺ����ѧ���� ������ѧ ���ξ��� ��ʷ���� ������");
  scanf("%s",r->category);
  p = l;
 if (p->next == NULL)
  {
   
    p->next = r;//���ӽڵ� 
    r->next = NULL;//�ÿ�rָ����
  }
 else
  {
   r->next = p->next;
   p->next = r;
   //ʵ�ֽ�r�ڵ�������� 
  }
 
 }
   printf("����ͼ����Ϣ�ɹ������ڷ������˵�") ;
}
void print(book**head)
{
	book*l = *head;
	book*p = l->next;
	if(p==NULL)
	{
	printf("û��ͼ�飡���ȴ���");
	return;
	}
do{

	printf("****************�鼮��Ϣ******************\n");
   printf(" ���:%d\n",p->number);
   printf(" ����:%s\n",p->name);     
   printf(" ����:%s\n",p->author);
   printf(" ������:%s\n",p->publish);
   printf(" ����:%s\n",p->category);
   p = p->next;
}while(p!=NULL);


}

