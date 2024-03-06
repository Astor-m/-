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
typedef struct
{
	int weight;					//Ȩֵ�������ɷŴ�ȡ����
	int parent,lchild,rchild;		//˫�׺ͺ��ӷ���
}HTNode,*HuffmanTree;					//�ö�̬����洢Huffman��
typedef  char**HuffmanCode;				//��̬����洢Huffman�����


void Select(HuffmanTree HT, int s, int &s1, int &s2)
{
	int i;
	int min1=RAND_MAX,min2=RAND_MAX;
	s1=-1;
	s2=-1;
	for(i=1;i<=s ;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<min2)
			{
				if(HT[i].weight<min1)
				{
					min2=min1;
					min1=HT[i].weight;
					s2=s1;
					s1=i;
				}
				else
				{
					min2=HT[i].weight;
					s2=i;
				}
			}
		}
	}
}


void  HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	HuffmanTree p;
	int i,m,s1,s2;
	int c,f,start;	//����ջ�ǵݹ�����շ�������շ�������ʱע������
	//int cdlen,k;	//��Ҷ�ӵ���������ÿ���ַ��Ĺ���������ʱע������
	char *cd;
	if(n<=1)
		return;
	m=2*n-1;    //n��Ҷ�ӵ�HuffmanTree����2n-1�����;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0��Ԫδ��
	for(p=HT+1,i=1; i<=n; ++i,++p,++w)
	{
		p->lchild=0;
		p->parent=0;
		p->rchild=0;
		p->weight=*w;
	}//��ǰn0����Ԫ��ʼ��
	
	for(;i<=m; ++i,++p)
	{
		p->lchild=0;
		p->parent=0;
		p->rchild=0;
		p->weight=0;
		
	}//��Ҷ��֮��Ĵ洢��Ԫ����
	for(i=n+1;i<=m; ++i)
	{    //��Huffman��(��Ҷ�Ӻ�ʼ���ڽ��) 
		Select(HT, i-1, s1, s2);   //��HT[1��i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�ΪS1��s2���̲�δ�����˺���Դ�룩
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+ HT[s2].weight;
	}
	//��Ҷ�ӵ���������ÿ���ַ��Ĺ���������
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));						//����n���ַ������ͷָ��������һά���飩
	cd=(char *) malloc(n*sizeof(char));								//���������Ĺ����ռ�(n) 
	cd[n-1]='\0';														//�������������cd[0]~cd[n-1]Ϊ�Ϸ��ռ䣩
	for(i=1;i<=n;++i)
	{																//����ַ���Huffman����
		start=n-1;														//���������λ��
		for(c=i,f=HT[i].parent;   f!=0;   c=f, f=HT[f].parent)			//��Ҷ�ӵ������������
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
			HC[i]=(char*)malloc((n-start)*sizeof(char));				//Ϊ��i���ַ��������ռ�
			strcpy(HC[i],&cd[start]);									//��cd���Ʊ��봮��HC
	}
///////////////////////////////////////////////////////////////////////
	/*
	//----------��ջ�ǵݹ�����շ�����,��շ�������
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char*) malloc(n*sizeof(char)); //���������Ĺ����ռ�(n) 
	k=m;
	cdlen=0;
	for(i=1;i<=m;++i)
		HT[i].weight=0;  //�����շ�����ʱ�������״̬��־
	while(k)
	{
		if(HT[k].weight==0) 		//����
		{		
			HT[k].weight=1;
			if(HT[k].lchild!=0)
			{
				k=HT[k].lchild;
				cd[cdlen++]='0';
			}
			else if(HT[k].rchild==0)      //�Ǽ�Ҷ�ӽ����ַ��ı���
			{
				HC[k]=(char *)malloc((cdlen+1) *sizeof(char));
				cd[cdlen]='\0';
				strcpy(HC[k],cd); //���Ʊ���(��)
			}
		}
		else if (HT[k].weight==1) //����
		{	
			HT[k].weight=2;
			if(HT[k].rchild!=0)
			{
				k=HT[k].rchild;
				cd[cdlen++]='1';
			}
		}
		else		 //HT[p].weight==2,�˻�
		{	
			HT[k].weight=0;
			k=HT[k].parent;	
			--cdlen;
			//�˵������,���볤�ȼ�1
		}//else
	}//while
//////////////////////////////////////////////////////////////
*/
	free(cd);	//�ͷŹ����ռ�	
}//HuffmanCoding

int main()
{
	int w[]={5, 6, 2, 4, 14, 23, 3, 11};
	int i,n;
	HuffmanTree tree;
	HuffmanCode HC;
	n=sizeof(w)/sizeof(int);
	HuffmanCoding(tree, HC, w, n);
	for(i=1;i<=n;i++)
	{
		printf("%s\n",HC[i]);
	}
	return 0;
}
