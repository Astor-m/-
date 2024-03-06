#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <string.h>
#include<vector>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<graphics.h>
using namespace std;

#define N 9999
#define INF 0x3f3f3f3f
int map[N][N];	//���ڽӾ�������ͼ��
int dis[N];		//���˼�¼Դ�㵽������ľ��룻
int vis[N];		//��Ƕ����Ƿ���ʹ�;
vector<int> path;
int p, q;//��p��q֮������·���� 
int num=0;
char city[28][10]={"��³ľ��","����","����","����","�ɶ�","����","����","����","����","����","����","̨��","����","�ϲ�","����","֣��","̫ԭ","ʯ��ׯ","���ͺ���","����","���","����","�Ϸ�","�Ͼ�","�Ϻ�","����","����","������"};
char city2[28][10]={"wlmq","ls","xn","lz","cd","cq","km","gy","nn","gz","hk","tb","fz","nc","xa","zz","ty","sjz","hhht","bj","tj","jn","hf","nj","sh","sy","cc","heb"};
char picture[28][10]={"wlmq.jpg","ls.jpg","xn.jpg","lz.jpg","cd.jpg","cq.jpg","km.jpg","gy.jpg","nn.jpg","gz.jpg","hk.jpg","tb.jpg","fz.jpg","nc.jpg","xa.jpg","zz.jpg","ty.jpg","sjz.jpg","hhht.jpg","bj.jpg","tj.jpg","jn.jpg","nj.jpg","sh.jpg","sy.jpg","cc.jpg","heb.jpg"};
int r[3][4]={{1010,10,1190,40},{1010,50,1190,80},{1010,640,1190,670}};//��ť����
int point[28][2]={{230,220},{225,520},{405,410},{445,420},{445,515},{505,545},{415,640},{485,620},{505,690},{615,690},//ÿ�����е�����
				  {455,740},{735,630},{695,620},{645,570},{520,440},{595,445},{580,370},{605,370},{560,320},{625,335},
				  {645,345},{645,395},{650,495},{680,505},{720,505},{730,285},{740,235},{760,195}};

int button_judge(int x,int y){//ʵ�������ѡ��
	if(x>r[0][0] && x<r[0][2] && y>r[0][1] && y<r[0][3])return 1;//���Ϊ��ʼ����
	if(x>r[1][0] && x<r[1][2] && y>r[1][1] && y<r[1][3])return 2;//���Ϊ���н���
	if(x>r[2][0] && x<r[2][2] && y>r[2][1] && y<r[2][3])return 3;//�˳�����
	return 0;
}

void inin(int n){//��ʼ����
	int i,j;
	memset(vis, 0, sizeof(vis));
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (i == j)
				map[i][j] = 0;
			else
				map[i][j] = INF;
		}
	}
	map[0][2]=1741;map[2][0]=1741;
	map[1][2]=1960;map[2][1]=1960;
	map[2][3]=194;map[3][2]=194;
	map[3][4]=599;map[4][3]=599;
	map[4][5]=250;map[5][4]=250;
	map[4][6]=638;map[6][4]=638;
	map[5][6]=500;map[6][5]=500;
	map[5][7]=384;map[7][5]=384;
	map[5][15]=844;map[15][4]=844;
	map[7][8]=512;map[8][7]=512;
	map[8][9]=500;map[9][8]=500;
	map[8][10]=800;map[10][8]=800;
	map[9][10]=584;map[10][9]=584;
	map[9][12]=680;map[12][9]=680;
	map[12][11]=250;map[11][12]=250;
	map[12][13]=582;map[13][12]=582;
	map[12][22]=660;map[22][12]=660;
	map[13][15]=975;map[15][13]=975;
	map[14][15]=434;map[15][14]=434;
	map[15][17]=392;map[17][15]=392;
	map[16][17]=244;map[17][16]=244;
	map[16][18]=531;map[18][16]=531;
	map[17][19]=331;map[19][17]=331;
	map[17][21]=303;map[21][17]=303;
	map[19][20]=120;map[20][19]=120;
	map[19][26]=976;map[26][19]=976;
	map[21][23]=667;map[23][21]=667;
	map[23][24]=265;map[24][23]=265;
	map[25][26]=302;map[26][25]=302;
	map[26][27]=242;map[27][26]=242;
}
void Dijkstra(int st,int n){
	int i, j, k, x;
	path=vector<int>(n,-1);
	for (i = 0; i < n; i++)//��dis�����¼Դ�㵽���������ӵĶ���ľ��룻
		dis[i] = map[st][i];
	vis[st] = 1;//��Ǹղ�Դ��,��ʾ�Ѿ����ʣ�
	while (1){
		x = -1;
		int min = INF;
		for (i = 0; i < n; i++){//�ڵ�ǰ��dis�����������ҵ�һ����С��·������������·����Ķ����¼��
			if (vis[i] != 1 && dis[i] < min){
				min = dis[i];
				x = i;
			}
		}
		vis[x] = 1;
		if (x == -1)//ֱ�����еĶ��㶼�ѷ��ʹ�������ѭ��
			break;
		for (i = 0 , k=0; i < n; i++){//����dis���飬
			if (vis[i] != 1 && dis[i] > min + map[x][i]){
				dis[i] = min + map[x][i];
				path[i]=x;
			}
		}
	}
}

void get_path(int x,vector<int>&P){
	if(!x){
		P.push_back(0);
		return;
	}
	if(path[x]!=-1)
		get_path(path[x],P);
	P.push_back(x);
	num++;
}

int main(){

	int p=-1,q=-1;
	vector<int> P;
	int start[2],end[2];
	inin(30);//��ʼ��ͼ
	initgraph(1200,1000);
	IMAGE img;
	IMAGE im;
	loadimage(&img,"a.jpg",1000,800);//�򿪵�ͼ
	putimage(0,0,&img);
	setbkmode(TRANSPARENT);
	settextstyle(30,0,"����");//sΪ���������硰���塱
	settextcolor(RED);
	outtextxy(450,10,"����ͼ");
	settextstyle(20,0,"����");
	
	RECT R1={r[0][0],r[0][1],r[0][2],r[0][3]};
	RECT R2={r[1][0],r[1][1],r[1][2],r[1][3]};
	RECT R3={r[2][0],r[2][1],r[2][2],r[2][3]};
	drawtext("��ʼ����",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("���н���",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("�˳�����",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	while(true){
	
		MOUSEMSG m;//���ָ��
		m = GetMouseMsg();//��ȡһ�������Ϣ
		switch(m.uMsg){
			case WM_LBUTTONDOWN://������
				switch(button_judge(m.x,m.y)){//�ж�������ĸ���ť

					case 1:
						setfillcolor(BLACK);
						solidrectangle(1010,10,1190,80);//����ʼ��Ϣ���ǣ������µ���Ϣ
						outtextxy(1000,10,"��㣺");
						rectangle(1100,10, 1190, 30);//���Ʊ߿�
						outtextxy(1000,40,"�յ㣺");
						rectangle(1100,40, 1190, 60);//���Ʊ߿�
						char a[10],b[10];
						InputBox(a,30,"��㣺");//����������
						InputBox(b,30,"�յ㣺");//�����յ����
						for(int i=0;i<28;i++){
							if(strcmp(a,city2[i])==0){
								p=i;
								outtextxy(1100,10,city[p]);
							}
							if(strcmp(b,city2[i])==0){
								q=i;
								outtextxy(1100,40,city[q]);
							}
						}
						if(p==-1||q==-1){
							outtextxy(1100,90,"�������");
							system("pause");
							return 0;
						}
						Dijkstra(p,28);
						get_path(q,P);
						setcolor(YELLOW);
						outtextxy(1000,70,"�Ƽ�·��:");
						outtextxy(1000,110,city[p]);//���
						char t[5];
						sprintf(t, "%d",dis[p]);
						outtextxy(1080,110,t);
						fillcircle(point[p][0],point[p][1],5);
						start[0]=point[p][0];
						start[1]=point[p][1];
						
						for(int i=0;i<num;i++){//��ӡ·��
							end[0]=point[P[i]][0];
							end[1]=point[P[i]][1];
							char s[10];
							sprintf(s, "%d",dis[P[i]]);
							setcolor(YELLOW);
							outtextxy(1000,130+i*20,city[P[i]]);
							outtextxy(1080,130+i*20,s);
							fillcircle(point[P[i]][0],point[P[i]][1],5);
							setcolor(RED);
							line(start[0],start[1],end[0],end[1]);
							start[0]=end[0];
							start[1]=end[1];
						}
						system("pause");
						break;
					case 2://���н���
							setfillcolor(BLACK);
							solidrectangle(1000,360,1200,400);
							setfillcolor(RED);
							char c[10];
							InputBox(c,30,"�����뿴�ĳ��У�");
							for(int i=0;i<28;i++){//���ҳ���
								if(strcmp(c,city2[i])==0){
									setcolor(YELLOW);
									settextstyle(14,0,"����");
									outtextxy(1000,380,city[i]);
									loadimage(&im,picture[i],200,200);
									putimage(1000,400,&im);
									break;
								}
							}
						getchar();
						break;
					case 3://ֱ���˳�����
						return 0;
					default:
						FlushMouseMsgBuffer();//�����¼�����������Ϣ
						//printf("\r\n(%d,%d)",m.x,m.y);//��ӡ������꣬�������ʱȷ������
						break;
				}
				break;
		}
	}
	getchar();
	closegraph();
	getchar();
	return 0;
}


						//fillrectangle(220,210,240,230);//��  230,220
						//fillrectangle(215,510,235,530);//����	225,520
						//fillrectangle(395,400,415,420);//����	405,410
						//fillrectangle(435,410,455,430);//����	445,420
						//fillrectangle(435,520,455,540);//�ɶ�	445,510
						//fillrectangle(485,535,515,555);//����	505,545
						//fillrectangle(405,630,425,650);//����	415,640
						//fillrectangle(475,610,495,630);//����	485,620
						//fillrectangle(495,680,515,700);//����	505,690
						//fillrectangle(595,670,615,690);//����	605,680
						////����	455,740
						//fillrectangle(725,620,755,640);//̨��	735,630
						//fillrectangle(685,610,705,630);//����	695,620
						//fillrectangle(635,560,655,580);//�ϲ�	645,570
						//fillrectangle(510,440,530,460);//����	515,430
						//fillrectangle(585,435,605,455);//֣��	595,445
						//fillrectangle(570,360,590,380);//̫ԭ	580,370
						//fillrectangle(595,360,615,380);//ʯ��ׯ	605,370
						//fillrectangle(550,310,570,330);//���ͺ���	560,320
						//fillrectangle(615,325,635,345);//����	625,335
						//fillrectangle(635,335,655,355);//���	645,345
						//fillrectangle(635,385,655,405);//����	645,395
						//fillrectangle(640,485,660,505);//�Ϸ�	650,495
						//fillrectangle(670,485,690,505);//�Ͼ�	680,505
						//fillrectangle(710,495,730,515);//�Ϻ�	720,505
						//fillrectangle(720,275,740,295);//����	730,285
						//fillrectangle(730,225,750,245);//����	740,235
						//fillrectangle(750,185,770,205);//������	760,195


