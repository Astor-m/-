// Graph.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define M  55555
#define MAXV 40
#define FALSE  0
#define TRUE   1

typedef struct  //ͼ�Ĵ洢����
{
	char vexs[MAXV][9];
	char xiaobin[MAXV][40];
	int  arcs[MAXV][MAXV];
	int  vexnum;
}MGraph;

int p[MAXV][MAXV][MAXV];
int d[MAXV][MAXV];


void chushi(MGraph &G)    //��ʼ��ͼ�� �൱������һ��ͼ
{
	int i, j;
	
	strcpy(G.vexs[0], "��³ľ��");
	strcpy(G.vexs[1], "����");
	strcpy(G.vexs[2], "����");
	strcpy(G.vexs[3], "���ͺ���");
	strcpy(G.vexs[4], "����");
	strcpy(G.vexs[5], "���");
	strcpy(G.vexs[6], "����");
	strcpy(G.vexs[7], "����");
	strcpy(G.vexs[8], "������");
	strcpy(G.vexs[9], "����");
	strcpy(G.vexs[10], "����");
	strcpy(G.vexs[11], "֣��");
	strcpy(G.vexs[12], "����");
	strcpy(G.vexs[13], "�ɶ�");
	strcpy(G.vexs[14], "�人");
	strcpy(G.vexs[15], "�Ϻ�");
	strcpy(G.vexs[16], "����");
	strcpy(G.vexs[17], "����");
	strcpy(G.vexs[18], "����");
	strcpy(G.vexs[19], "�ϲ�");
	strcpy(G.vexs[20], "����");
	strcpy(G.vexs[21], "����");
	strcpy(G.vexs[22], "����");
	strcpy(G.vexs[23], "����");
	strcpy(G.vexs[24], "����");

	
	G.vexnum=25;
	
	for(i=0; i<G.vexnum; i++)
		for(j=0; j<i; j++)
			G.arcs[i][j]=M;
			
	for(i=0; i<G.vexnum; i++)
		G.arcs[i][i]=0;

    for(i=0; i<G.vexnum; i++)
		for(j=i; j<G.vexnum; j++)
			G.arcs[i][j]=M;

    G.arcs[0][2]=1892,  G.arcs[1][2]=216,   G.arcs[2][3]=1145,    G.arcs[3][4]=668,   G.arcs[4][5]=137;
    G.arcs[11][12]=349, G.arcs[5][6]=704,   G.arcs[6][7]=305,     G.arcs[6][9]=397,   G.arcs[7][8]=242;
    G.arcs[10][13]=842, G.arcs[2][10]=676,  G.arcs[10][11]=511,   G.arcs[4][11]=695,  G.arcs[5][12]=674;
    G.arcs[11][14]=534, G.arcs[12][15]=651, G.arcs[13][16]=1100,  G.arcs[13][17]=967, G.arcs[16][17]=639;
    G.arcs[17][18]=902, G.arcs[17][21]=607, G.arcs[21][22]=255,   G.arcs[18][21]=672, G.arcs[18][14]=409;
    G.arcs[18][19]=367, G.arcs[18][23]=675, G.arcs[23][24]=140,   G.arcs[19][20]=622, G.arcs[15][19]=825;
    
    for(i=0; i<G.vexnum; i++)
       for(j=i; j<G.vexnum; j++)
       	   if(G.arcs[i][j]!=M && G.arcs[j][i]==M)
       	       G.arcs[j][i]=G.arcs[i][j];
       	       
    strcpy(G.xiaobin[0], "�й��������ߵĴ���У�");
	strcpy(G.xiaobin[1], "����, �ã��п�ȥ��!");
	strcpy(G.xiaobin[2], "����պ������ĵط���");
	strcpy(G.xiaobin[3], "�п�ȥ��ʶ��ʶ�������!");
	strcpy(G.xiaobin[4], "�й��׶�");
	strcpy(G.xiaobin[5], "�黨�������������һ�û�гԹ���");
	strcpy(G.xiaobin[6], "�ǲ��ǹ�ҵ���أ��һ������!");
	strcpy(G.xiaobin[7], "Ҫ��������Զ�Ǵ���ͺ���!");
	strcpy(G.xiaobin[8], "�����Ư��");
	strcpy(G.xiaobin[9], "�����и���ۿ�!");
	strcpy(G.xiaobin[10], "����ٸ����ʧ����");
	strcpy(G.xiaobin[11], "���й����в�");
	strcpy(G.xiaobin[12], "Ҳ����һ�����찡! �Ǻ�!");
	strcpy(G.xiaobin[13], "û��˵����");
	strcpy(G.xiaobin[14], " �õط���");
	strcpy(G.xiaobin[15], "����ȥ��һ���ĵط���");
	strcpy(G.xiaobin[16], "��˵���ļ��紺�ĵط�");
	strcpy(G.xiaobin[17], "̫����ϡ�еĵط���������ô�й���!?");
	strcpy(G.xiaobin[18], "��˵�ǻ������ĳ��У�");
	strcpy(G.xiaobin[19], "��һ���壡");
	strcpy(G.xiaobin[20], "���˽�");
	strcpy(G.xiaobin[21], "����һ��������ô��!");
	strcpy(G.xiaobin[22], "������ˣ����Ǻ��ϰ���");
	strcpy(G.xiaobin[23], "�����ڹ��ݴ򹤣�");
	strcpy(G.xiaobin[24], "����������");
}


void ShortestPath_FLOYD(MGraph g)//�����·��
{
	int i, j, k, l;
	
	for(i=0; i<g.vexnum; i++)
		for(j=0; j<g.vexnum; j++)
		{
		    d[i][j]=g.arcs[i][j];
		    for(k=0; k<g.vexnum; k++)
		        p[i][j][k]=FALSE;
		    if(d[i][j]<M)
		    {
		    	p[i][j][i]=TRUE;
		    	p[i][j][j]=TRUE;
		    }
		}
		
	for(k=0; k<g.vexnum; k++)
	    for(i=0; i<g.vexnum; i++)
	        for(j=0; j<g.vexnum; j++)
	            if(d[i][k]+d[k][j]<d[i][j])
	            {
	            	d[i][j]=d[i][k]+d[k][j];
	            	for(l=0; l<g.vexnum; l++)
	            	    p[i][j][l]=p[i][k][l] || p[k][j][l];
	            }    
}


void windows(char &a)
{
	do
	{
	    system("cls");	
	    printf("\n\t�X�����������������������������������������������������������[\n\t��");
	    printf("\t\t\t\t\t\t\t    ��\n\t��\t\t\t * ����˵�� *\t\t\t    ��\n\t��");
	    printf("\t\t\t\t\t\t\t    ��\n\t��    ���н�˵--------j\t\t\t�г�ָ��---------z  ��\n\t��");
	    printf("\t\t\t\t\t\t\t    ��\n\t��\t\t\t\t\t�˳�����---------t  ��");
	    printf("\n\t�^�����������������������������������������������������������a\n");
		printf("\n\n\t��ѡ�����:");
		a=getch();
	}while(a!='j' && a!='z' && a!='t');
}

void print(MGraph g)
{
	int i;
	printf("\n\n\t    %d.%s\n\t   ", 0, g.vexs[0]);
	for(i=1; i<g.vexnum; i++)
	{
		printf("%2d.%-8s", i, g.vexs[i]);
		if(!(i%6))
		printf("\n\t   ");
	}
}


void reprint()
{
   	system("cls");
    printf("\n\t�������! ����������!%c\n", 7);
}


void choose1(MGraph g, int &num)
{  
    do
    { 
    	print(g);
        printf("\n\n\t��ѡ����Ҫ�˽�ĳ���:");
        scanf("%d", &num);
        if (num<0 || num>=g.vexnum)
        reprint();
    }while(num<0 || num>=g.vexnum);
}


void choose2(MGraph g, int &num)
{  
    do
    { 
    	print(g);
        printf("\n\n\t��ѡ����Ҫ��������:");
        scanf("%d", &num);
        if (num<0 || num>=g.vexnum)
        reprint();
    }while(num<0 || num>=g.vexnum);
}


void choose3(MGraph g, int &num, int m)
{  
    do
    { 
        print(g);
        printf("\n\t���ղ�ѡ���������Ϊ: %s !\n", g.vexs[m]);
        printf("\n\t����,��ѡ����Ҫ��Ŀ�ĳ���:");
        scanf("%d", &num);
        if(num==m)
        {
             printf("\n\n\t\t��Ǹ,��ѡ�������к��յ����Ϊͬһ����!%c", 7);
             printf("\n\n\t\t ����������!");
             getch();
             system("cls");
        }
        if (num<0 || num>=g.vexnum)
        reprint();
    }while(num<0 || num>=g.vexnum || num==m);
}


void find(MGraph g)
{
	int a, b, i, j, l, m, fz[MAXV];
	choose2(g, a);
	choose3(g, b, a);
	printf("\n\t\t��%s��%s�����·����%dǧ��!", g.vexs[a], g.vexs[b], d[a][b]);
	printf("\n\n\t\t·��Ϊ:\n");
	for(i=0, j=0; i<g.vexnum; i++)
	    if(p[a][b][i])
	        fz[j++]=i;         //�������¼·���ϵĳ���
	for(m=0, l=1; m<j; m++)       //·�����ܹ���j������Ҫ���
	    for(i=0; i<j; i++)     //����d[a]ֱ�������ĳ���
	       if(g.arcs[a][fz[i]]!=M)//��Ҫ�Ǹ���;��������
	       {
	          printf("\n\t\t\t%d.%s--%dKm", l++, g.vexs[fz[i]], g.arcs[a][fz[i]]);
	          g.arcs[fz[i]][a]=M;
		      a=fz[i];
	       }
	getch();
}


void jieshao(MGraph g, int n) //���������Ϣ����
{
	printf("\n\t\t%s", g.xiaobin[n]);
	getch();
}


void choose(MGraph g, char c)
{
	int h;
	switch(c)
	{
	    case 'z':
                find(g);
		        break;
	    case 'j':
	            choose1(g, h);
		        jieshao(g, h);
	}
}


int main()
{
	char a;
	MGraph g;    //����һ��ͼ
	
	chushi(g);   //����һ��ͼ
	ShortestPath_FLOYD(g);   //�����֮������·��
	
	do
    {
        windows(a);         // ��ʾ����
        choose(g, a);
    }while(a!='t');
	return 0;
}
