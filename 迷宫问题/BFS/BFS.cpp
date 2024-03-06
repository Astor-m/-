#include<bits/stdc++.h>
using namespace std;

int a[100][100],v[100][100];
int n,m;
int startx,starty,endx,endy;
struct point{
	int x,y;
	int step;
	point(int a=0,int b=0,int c=0):x(a),y(b),step(c){}
};
queue<point> que;//����
int dirx[]={1,0,-1,0};
int diry[]={0,-1,0,1};
int b[100];
stack<point> st;
int pathnum;

/*
5 4
0 0 1 0
0 0 0 0
0 0 1 0
0 1 0 0
0 0 0 1
1 1
4 3

6 6
0 0 1 1 0 1
1 0 0 1 0 1
1 0 1 1 0 1
1 0 0 0 0 1
1 1 0 0 0 1
1 1 1 1 0 1
1 1
6 5
*/

//ջ�����һ�ȥ��· 
void path(){
	v[endx][endy]=pathnum;
	point P(endx,endy,pathnum);
	st.push(P);
	int px=endx,py=endy;
	while(v[px][py]!=1){
		for(int i=0;i<4;i++)
			if((v[px][py]-1)==v[px+dirx[i]][py+diry[i]]){
				px=px+dirx[i];
				py=py+diry[i];
				point Q(px,py,v[px][py]);
				st.push(Q);
				break;
		}
	}
}

void print(){
	while(!st.empty()){
		cout<<st.top().x<<" "<<st.top().y<<" "<<st.top().step<<endl;
		st.pop();
	}
}

/*
void print(){

	int tx=startx,ty=starty;
	while(tx!=endx&&ty!=endy){
		for(int i=0;i<4;i++)
			if(v[tx+dirx[i]][ty+diry[i]]==(v[tx][ty]+1)){
				tx=tx+dirx[i];
				ty=ty+diry[i];
				cout<<tx<<" "<<ty<<" "<<v[tx][ty]<<endl;
				continue;
		}
	}
}
*/
void BFS(point p){
	int status=0;
	que.push(p);
	v[startx][starty]=1;
	while(!que.empty()){
		int x=que.front().x,y=que.front().y;
		if(x==endx&&y==endy){//�����յ� 
			status=1;
			pathnum=que.front().step;
			cout<<"��̲�����"<<que.front().step<<endl;
			que.pop();
			break;
		}
		for(int i=0;i<4;i++){
			int tx=x+dirx[i],ty=diry[i]+y;
			if(a[tx][ty]==0&&v[tx][ty]==0){
				point temp(tx,ty,que.front().step+1);
				v[tx][ty]=que.front().step+1;
				que.push(temp);
			}
		}
		que.pop();
	}
	if(!status)
		cout<<"no way!"<<endl;
}

void makemaze(){
	cout<<"�����Թ�����"<<endl;
	cin>>n>>m;
	cout<<"�����Թ�(1ǽ�壬0����·)��"<<endl;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	cout<<"�Թ��壺"<<endl;
	for(int i=1;i<=n;i++){
		cout<<endl;
		for(int j=1;j<=m;j++)
			if(a[i][j]==0)
				cout<<" "<<" ";
			else
				cout<<"*"<<" ";
			}
	cout<<endl<<"����������꣺";
	cin>>startx>>starty;
	cout<<"�����յ����꣺";
	cin>>endx>>endy;
}
 
int main(){
	makemaze();
	point pstart(startx,starty,0);
	BFS(pstart);
//	v[startx][starty]=0;
	for(int i=1;i<=n;i++){
		cout<<endl;
		for(int j=1;j<=m;j++)
			cout<<v[i][j]<<" ";
}
	cout<<endl<<"���·����"<<endl;
	path();
	print();
	return 0;
}
