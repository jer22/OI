#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define inf (1e8)
int N;
int A[100][100],B[100][100],W[100][100],visx[100],visy[100],lx[100],ly[100],link[100],slack[100];
struct node{int a,b;};

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

bool dfs(int x){
	visx[x]=1;
	for(int i=1;i<=N;i++){
		if(visy[i])continue;
		int t=lx[x]+ly[i]-W[x][i];
		if(t==0){
			visy[i]=1;
			if(link[i]==-1||dfs(link[i])){
				link[i]=x; return true;
			}
		}
		else slack[i]=min(slack[i],t);
	}
	return false;
}

node KM(){
	memset(link,-1,sizeof(link)); memset(ly,0,sizeof(ly));
	for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)
			lx[i]=max(lx[i],W[i][j]);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++)
			slack[j]=inf;
		while(1){
			memset(visx,0,sizeof(visx)); memset(visy,0,sizeof(visy));
			if(dfs(i))break;
			int d=inf;
			for(int j=1;j<=N;j++)
				if(!visy[j])d=min(d,slack[j]);
			for(int j=1;j<=N;j++)
				if(visx[j])lx[j]-=d;
			for(int j=1;j<=N;j++)
				if(visy[j])ly[j]+=d;
				else slack[j]-=d;
		}
	}
	int tota=0,totb=0;
	for(int i=1;i<=N;i++)
		if(link[i]!=-1){tota+=A[link[i]][i]; totb+=B[link[i]][i];}
	node x; x.a=tota; x.b=totb;
	return x;
}

int ask(node L,node R){
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			W[i][j]=(R.b-L.b)*A[i][j]+(L.a-R.a)*B[i][j];
	node t=KM();
	if((t.a==L.a && t.b==L.b) || (t.a==R.a && t.b==R.b))
		return min(L.a*L.b,R.a*R.b);
	else return min(ask(L,t),ask(t,R));
}

int main(){
	freopen("3571.in", "r", stdin);
	int T=read();
	while(T--){
		N=read();
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				A[i][j]=read();
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				B[i][j]=read();
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				W[i][j]=-A[i][j];
		node L=KM();
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				W[i][j]=-B[i][j];
		node R=KM();
		int ans=ask(L,R); printf("%d\n",ans);
	}
	return 0;
}