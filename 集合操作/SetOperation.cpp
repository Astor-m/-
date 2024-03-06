// ���ݽṹ1.cpp : �������̨Ӧ�ó������ڵ㡣
//


#define  TRUE 1
#define  FALSE   0
#define  OK  1
#define  ERROR   0
#define INFEASIBLE   -1
#define OVERFLOW   -2
typedef  int  Status;
typedef  char  ElemType;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef  struct NodeType
{
	ElemType   data;
	struct NodeType  *next;
} NodeType,*LinkType;

typedef struct
{
	LinkType head,tail;//ָ�������ͷ��β
	int size;
}OrderedList;

ElemType a[100]="magazine";//set1��ʼֵ
ElemType b[100]="paper";
OrderedList L1,L2,L3;

Status MakeNode(LinkType &p,ElemType e)//�ӳ����� 
{
	p=(LinkType)malloc(sizeof(NodeType));
	if(!p)
		return FALSE;
	p->data=e;
	p->next=NULL;
	return TRUE;
}

Status InitList(OrderedList &L)//��ʼ������ ��ͷ��㶨��Ϊ�� 
{
	if(MakeNode(L.head,' '))
	{
		L.tail=L.head;
		L.size=0;
		return TRUE;
	}
	else
	{
		L.head=NULL;
		return FALSE;
	}
}
Status LocateElem(OrderedList L,  ElemType e,  LinkType &p)//����Ԫ��e�ڱ�L1�е�λ��
{
	NodeType *pre;
	if(L.head)
	{
		pre=L.head;
		p=pre->next;
		while(p && p->data<e)
		{
			pre=p;
			p=p->next;
		}
		if(p && p->data==e)//���ҳɹ�
		{
			return TRUE;
		}
		else
		{
			p=pre;
			return FALSE;
		}
	}
	else
		return FALSE;
}

void InsertAfter(OrderedList L,  LinkType q,  LinkType s)//������β����½��
{
	if(L.head && q && s)
	{
		s->next=q->next;
		q->next=s;
		if(L.tail==q)
			L.tail=s;
		L.size++;
	}
}

void CreateSet(OrderedList &T, char *s)//�����ַ�������ȥ���ظ��ַ��ͷ�a~z�ַ� 
{
	unsigned i;
	LinkType p ,q;
	if(InitList(T))
	{
		for(i=0;i<=strlen(s);i++)
		{
			if(s[i]>='a' &&s[i]<='z' &&  !LocateElem(T,s[i],p))
			{
				if(MakeNode(q,s[i]))
				{
					InsertAfter(T,p,q);
				}
			}
		}
	}
}
Status Print(LinkType p)
{
	if(p)
	{
		printf("%c",p->data);
		return TRUE;
	}
	else
		return FALSE;
}

void ListTraverse(LinkType p, Status (*visit)( LinkType ))
{
	printf("%c",'\t');
	while(p)
	{
		visit(p);
		p=p->next;
	}
	printf("%c",'\n');
	
}

void Append(OrderedList &L,LinkType s)//L=L3������L3
{
	if(L.head && s)//��L3�ı�β���Ԫ��
	{
		if(L.tail!=L.head)
			L.tail->next=s;
		else
			L.head->next=s;
		L.tail=s;
		L.size++;
	}
}


void Union(OrderedList &T,OrderedList S1,OrderedList S2)//T=L3,S1=L1,S2=L2����L1��L2�ĺϼ�������L3����
{
	LinkType p1,p2,p;
	if(InitList(T))		
	{
		p1=S1.head->next;
		p2=S2.head->next;
		while( p1 && p2)//��ָ��δԽ��ʱѭ��
		{
			if(p1->data<=p2->data)//
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p1->data;
				p->next=NULL;
				Append(T,p);				
				if(p1->data==p2->data)
					p2=p2->next;
				p1=p1->next;
			}
			else
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p2->data;
				p->next=NULL;
				Append(T,p);
				p2=p2->next;
			}
		}
		while(p1)//p2������p1����Ԫ��
		{
			p=(LinkType)malloc(sizeof(NodeType));
			p->data=p1->data;
			p->next=NULL;
			Append(T,p);
			p1=p1->next;
		}
		while(p2)//p1������p2����Ԫ��
		{
			p=(LinkType)malloc(sizeof(NodeType));
			p->data=p2->data;
			p->next=NULL;
			Append(T,p);
			p2=p2->next;
		}
	}
}

void Intersection(OrderedList &T,OrderedList S1,OrderedList S2)//T=L3,S1=L1,S2=L2����L1��L2�Ľ���������L3
{
	LinkType p1,p2,p;
	if(!InitList(T))
		T.head=NULL;
	else
	{
		p1=S1.head->next;
		p2=S2.head->next;
		while( p1 && p2)
		{
			if(p1->data<p2->data)
				p1=p1->next;
			else if(p1->data>p2->data)
				p2=p2->next;
			else
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p1->data;
				p->next=NULL;
				Append(T,p);				
				p2=p2->next;
				p1=p1->next;
			}
		}
	}
}

void Difference(OrderedList &T,OrderedList S1,OrderedList S2)//��
{
	LinkType p1,p2,p;
	if(!InitList(T))
		T.head=NULL;
	else
	{
		p1=S1.head->next;
		p2=S2.head->next;
		while( p1 && p2)
		{
			if(p1->data<p2->data)
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p1->data;
				p->next=NULL;
				Append(T,p);
				p1=p1->next;
			}
			else if(p1->data>p2->data)
				p2=p2->next;
			else
			{
				p1=p1->next;				
				p2=p2->next;
			}
		}
		while(p1)
		{
			p=(LinkType)malloc(sizeof(NodeType));
			p->data=p1->data;
			p->next=NULL;
			Append(T,p);
			p1=p1->next;
		}
		
	}
}

void ReadCommand(char &cmd)//��ӡ��������
{
	printf("\n--------------------------------------------------------------------------\n");
	printf("\n\t\t\t\t��  ��  ��  ʾ");
	printf("\n--------------------------------------------------------------------------\n");
	printf("\tMakeSet1------1\t\t\t\tMakeSet2--------2\n\tUnion---------u\t\t\t\tIntersection----i\n\tDifference----d\t\t\t\tQuit------------q\n\tDisplay-------y");
	do{
		printf("\n\n\t��ѡ�������");
		cmd=getch();//�����������
		printf("\n--------------------------------------------------------------------------\n");
	}while(cmd!='1' && cmd!='2' && cmd!='u' && cmd!='i' && cmd!='d' && cmd!='q' && cmd!='y');
}
void Interpret(char &cmd)
{
	system("cls");   //����
	switch(cmd)
	{
	case '1'://����set1
		printf("\n\t�������ַ�����");
		gets(a);//�Ƚ��õ��������a��
		printf("\tԭʼ�ַ���:");
		printf("\t%s\n",a);
		CreateSet(L1, a);//��set1��a-z����Li������ȥ���ظ�Ԫ��
		printf("\t�����ļ���:");
		ListTraverse(L1.head->next,Print);//��ӡ�����õ�L1����
		break;
	case '2'://��case1������ͬ
		printf("\n\t�������ַ�����");
		gets(b);
		printf("\tԭʼ�ַ���:");
		printf("\t%s\n",b);
		CreateSet(L2, b);
		printf("\t�����ļ���:");
		ListTraverse(L2.head->next,Print);
		break;
	case 'u'://��ϼ�
		CreateSet(L1, a);
		CreateSet(L2, b);
		Union(L3,L1,L2);
		printf("\n\t����1:");
		ListTraverse(L1.head->next,Print);
		printf("\t����2:");
		ListTraverse(L2.head->next,Print);
		printf("\t����:");
		ListTraverse(L3.head->next,Print);
		break;
	case 'i'://�󽻼�
		CreateSet(L1, a);
		CreateSet(L2, b);
		Intersection(L3,L1,L2);
		printf("\n\t����1:");
		ListTraverse(L1.head->next,Print);
		printf("\t����2:");
		ListTraverse(L2.head->next,Print);
		printf("\t����:");
		ListTraverse(L3.head->next,Print);
		break;
	case 'd'://��
		CreateSet(L1, a);
		CreateSet(L2, b);
		Difference(L3,L1,L2);
		printf("\n\t����1:");
		ListTraverse(L1.head->next,Print);
		printf("\t����2:");
		ListTraverse(L2.head->next,Print);
		printf("\t�:");
		ListTraverse(L3.head->next,Print);
		break;
	case 'y'://��ӡ���������
		printf("\n\tԭʼ�ַ���:\n");
		printf("\t\t%s\n\t\t%s\n",a,b);		
		CreateSet(L1, a);
		CreateSet(L2, b);
		printf("\t���ַ��������ļ���:\n");
		printf("\t");
		ListTraverse(L1.head->next,Print);
		printf("\t");
		ListTraverse(L2.head->next,Print);
		Union(L3,L1,L2);
		printf("\t����:");
		ListTraverse(L3.head->next,Print);
		
		Intersection(L3,L1,L2);
		printf("\t����:");
		ListTraverse(L3.head->next,Print);
		
		Difference(L3,L1,L2);
		printf("\t�:");
		ListTraverse(L3.head->next,Print);
		break;
	}	
}
int main()
{
	char cmd;//�������	
	do
	{
		ReadCommand(cmd);
		Interpret(cmd);
	}while(cmd!='q');
	return 0;
}



