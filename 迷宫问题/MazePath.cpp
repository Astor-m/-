
// MazePath.cpp : �������̨Ӧ�ó������ڵ㡣
//

#define  TRUE 1
#define  FALSE   0
#define  OK  1
#define  ERROR   0
#define INFEASIBLE   -1
#define OVERFLOW   -2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
typedef  int  Status;
#define  RANGE   20		//RANGEΪʵ�ʷ���Ŀռ�������
#define M 8				//maze��������� 
#define N 11			// maze��������� 
typedef struct			//����Թ�Ԫ��λ����Ϣ������
{
	int r,c;
}PosType;

typedef struct//m��nΪ��������Թ�����������RANGEΪʵ�ʷ���Ŀռ�������
{
	int m,n;
	char arr[RANGE][RANGE];
}MazeType;

typedef int directiveType;//�����ϱ�������1��2��3��4������Ӧ

typedef struct//·������ջ���洢���˴�����ջԪ�������������Ϣ
{
	int step;//�洢����õ�ʱ�����Ĳ���
	PosType seat;//�õ�λ��
	directiveType di;//�Ӹõ�λ��������һλ�õķ���
}ElemType;

typedef struct NodeType//·��������ջ���洢
{
	ElemType data;
	struct NodeType *next;
}NodeType,*LinkType;

typedef struct//����ջ��ͷָ���Ԫ�ظ������з�װ
{
	LinkType top;
	int size;
}Stack;
//�����ǶԴ洢�ṹ�����ж���
void   InitStack(Stack  &S)   
{   //��������ջ������ͷ���
	S.top=NULL;   
	S.size=0;   
}   
Status   MakeNode(LinkType &p,ElemType   e)   
{   //����һ���½�㣬�Ա���룬����������Ϊ��ʽ�洢��������ͨ�ú�����������������ջ�����ӵĲ������
	p=(NodeType *)malloc(sizeof(NodeType));   
	if(!p)
		return   FALSE;   
	p->data=e;
	p->next=NULL;   
	return   TRUE;   
}

Status   Push(Stack   &S,ElemType   e)   
{   //��ջ�����������ﱾ������ջͷ������ͷ�����в���
	LinkType   p;   
	if(MakeNode(p,e))   
	{   
		p->next=S.top;   
		S.top=p;   
		S.size++;   
		return   TRUE;   
	}   
	return   FALSE;   
}

Status   StackEmpty(Stack   S)   
{   //�ж��Ƿ�Ϊ��ջ��������ͨ��topָ��ΪNULL���жϵģ�������Ҳ����ͨ��size�Ƿ�Ϊ0���ж�
	if(S.top==NULL)
		return   TRUE; 
	return  FALSE;   
}  

Status   Pop(Stack   &S,ElemType   &e) 
{	//��ջ��������������ɾ����ͷԪ��
	LinkType   p;
	if(StackEmpty(S)) 
		return   FALSE; 
	else
	{ 
		p=S.top;
		S.top=S.top->next; 
		e=p->data; 
		S.size--; 
		free(p);
		return   TRUE;
	} 		  
}   

Status   pass(MazeType  maze,PosType  curpos)//�жϸ�λ���Ƿ���� 
{   //�ж��Թ�Maze�У���ǰλ��curpos�Ƿ���һ���ɴ�λ��
	int   m,n;   //ע�������m��nֻ�Ǳ���±����ʱ��������ǰ����ֵ�m��n�ǲ�һ����
	m=curpos.r;   
	n=curpos.c;   
	if(maze.arr[m][n]==' ')
		return   TRUE;   
	return   FALSE;   
}

Status   Same(PosType  curpos,PosType  end)   
{   //�жϵ�ǰλ��curpos�Ƿ��Ѵ����
	if(curpos.r==end.r && curpos.c==end.c)
		return   TRUE;   
	return   FALSE;   
}

void   FootPrint(MazeType &maze,PosType curpos)   
{   //���Թ��б�ʶ�߹���λ�ã���������·����ʱ���߻�ͷ·������ѭ��
	int   m,n;   
	m=curpos.r;   
	n=curpos.c;   
	maze.arr[m][n]='-';   
}

PosType   NextPos(PosType curpos,int di)   
{   //ͨ��di��ֵ��ȷ����һ����λ�ã���һ��λ��ʵ���ǵ�ǰλ�õ��ĸ��ھ��е�һ��
	switch(di)
	{
	case 1:
		curpos.c++; //����
		break;		
	case 2:
		curpos.r++; //������
		break;
	case 3:
		curpos.c--; //������
		break;		
	case 4:
		curpos.r--;  //���� 
		break;
	}	
	return   curpos;  	
} 

void  MarkPrint(MazeType &maze,PosType p)   
{   //����̽��·���ߺ���˵�λ���������ʶ
	maze.arr[p.r][p.c]='@';   
}

void  PrintMaze(MazeType ma)   
{	//���Թ������ʵ���Ƕ�һ����ά��������
	int i,j;
	printf("\n"); 
	for(i=0;i<ma.m;i++)   
	{   
		printf("\t");
		for(j=0;j<ma.n;j++)   
		{   
			printf("%c ",ma.arr[i][j]);   
		}   
		printf("\n");   
	} 
	printf("\n"); 
} 


void   InitMaze(MazeType  &maze,int  a[][N],int row,int col)   
{   //���ݶ�ά��������ʼ���Թ��������ά����������Ϊ���û��Ӽ������룬�����ͬ�Թ������⣬�������û��ӿڲ������ǿ��ǵ��ص�
	//���ݽṹѧϰʱ���������������ֱ��Ƕ�뵽�����У��Լ������Լʱ��
	//��ά������a������ʱ����Ҫ֪�������Ķ�ά�������������ΪC�����ж�ά�����ǰ�������˳��洢��
	//����ÿ�г��ȵ�ʵ�ʾ��Ƕ����е���ֵ������Ҫ��ȷ����N
	int i,j;
	maze.m=row;
	maze.n=col;	
	for(i=0;i<row;i++)   
		for(j=0;j<col;j++)   
		{   
			if(a[i][j]==0)
				maze.arr[i][j]=' '; 
			else
				maze.arr[i][j]='#';   
		}   
} 
/*
int   MazePath(MazeType &maze,PosType start,PosType end)   
{   //����Թ��Ĺؼ�������maze��Ϊ�����ͱ�������ΪҪ�����·����һЩ��ʶ
//����ֵΪ·���ĳ���,����0��ʾ��ͨ·
Stack   s;   
int   curstep=1;   //ͳ��·������ʵ�ʿɲ���curstep��ջs�е�size�������������Ϣ���޸�һ�³���curstep��������ͳ���߹����ܲ���
int   found=0;   
ElemType   e;   //��ջԪ�ص���ʽ�ݴ浱ǰλ�õ������Ϣ���Ա���ջ����·��
PosType   curpos=start; //�ÿ�ʼλ��Ϊ��ǰλ��
InitStack(s);
do{   //ջ������δ�����������ѭ��
if(pass(maze,curpos))   //���curposλ�ÿɴ�������ջ
{   
FootPrint(maze,curpos);   //�����ͨ����Ϊ-����Ȼ����緢��������ͬ��������±��Ϊ����ķ���
e.step=curstep;   
e.seat=curpos;   
e.di=1;			   
Push(s,e);   
if(Same(curpos,end))
{
found=s.size;
printf("·��Ϊ��ǰ��λΪ�±꣬��һλΪ���򣩣�\n");
while(!StackEmpty(s))//���·��
{
Pop(s,e);
printf("%d,%d,%d\n",e.seat.r,e.seat.c,e.di);
}
}
else
{   
curpos=NextPos(curpos,1);  //����λ��ʱĬ�������� 
curstep++;   
}   
}   
else if(!StackEmpty(s))   
{   
Pop(s,e);   //���curposλ�ò��ɴ��ջ���գ���Ѹ���ջ��Ԫ�ص���������ж�
while((e.di==4) && !StackEmpty(s))
{   
MarkPrint(maze,e.seat); //��ʶ��·��ͨ  
Pop(s,e);   //�ص���һ��λ��
curstep--;   //����һ�Ļ���������ͳ���߹����ܲ���
}   
if(e.di<4)//������з���δ�߹��������µķ��������̽
{   
e.di++;   
Push(s,e);  //Ĭ���·������һλ�ÿɴ����ǰλ����ջ 
curpos=NextPos(e.seat,e.di);  //ͨ����ǰλ�ã��Լ�ȥ��һλ�õķ���ó��µ�λ�ã���ѭ���鿴��λ���Ƿ�ɴ� 
}
}		
}while(!StackEmpty(s) && !found);   
return   found-1;   
}  

*/
int  MazePath(MazeType &maze,PosType start,PosType end) 
{//�˺���Ϊ�ݹ鷽�����Թ����㷨
	static int steps=1;
	if(Same(start,end))
	{
		FootPrint(maze,start);
		printf("·��Ϊ��ǰ��λΪ�±꣬��һλΪ���򣩣�\n");
		printf("%d,%d\n",start.r,start.c);
		return steps;
	}
	else if(pass(maze,start))//�жϸ÷����Ƿ������ 
	{
		FootPrint(maze,start);
		if(MazePath(maze,NextPos(start,1),end))//������ 
		{
			printf("%d,%d,%d\n",start.r,start.c,1);
			return steps++;
		}
		else if(MazePath(maze,NextPos(start,2),end))//������ 
		{
			printf("%d,%d,%d\n",start.r,start.c,2);
			return steps++;
		}
		else if(MazePath(maze,NextPos(start,3),end))//������ 
		{
			printf("%d,%d,%d\n",start.r,start.c,3);
			return steps++;
		}
		else if(MazePath(maze,NextPos(start,4),end))//������ 
		{
			printf("%d,%d,%d\n",start.r,start.c,4);
			return steps++;
		}
		else
		{
			MarkPrint(maze,start);
			return FALSE;
		}
	}
	else//������ 
	{
		return FALSE;
	}
}

void Print(int maze[][N])
{
	int i,j;
	printf("��ʾ�Թ�������\n");
	for(i=0;i<M;i++)//8�� 
	{
		printf("\t");
		for(j=0;j<N;j++)//11�� 
		{
			printf("%d ",maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int main()
{
	int step=0;
	int maze[M][N]={
		1,1,1,1,1,1,1,1,1,1,1,
		1,0,1,0,0,1,1,1,0,0,1,
		1,0,0,0,0,0,1,0,0,1,1,
		1,0,1,1,1,0,0,0,1,1,1,
		1,0,0,0,1,0,1,1,0,1,1,
		1,1,0,0,1,0,1,1,0,0,1,
		1,1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1};
		MazeType L;
		PosType   start,end;
		Print(maze);
		InitMaze(L,maze,M,N);
		start.r=1;//��� 
		start.c=1;
		end.r=6;//�յ� 
		end.c=9;
		printf("������ת�������Թ�");
		PrintMaze(L);
		if(step=MazePath(L,start,end))
			printf("�Թ���·������-��ʾ,·������Ϊ:%d",step);
		else
			printf("���Թ�û��ͨ·��");
		PrintMaze(L);
		getch();
	return 0;
}

