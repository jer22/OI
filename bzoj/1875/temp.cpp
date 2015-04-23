#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define pa pair<int,int>
#define ll long long 
#define mod 45989
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int cnt=1,n,m,t,A,B;
int last[25];
struct edge{
	int from,to,next,v;
}e[1005];
void insert(int u,int v)
{
	e[++cnt].to=v;e[cnt].from=u;e[cnt].next=last[u];last[u]=cnt;
	e[++cnt].to=u;e[cnt].from=v;e[cnt].next=last[v];last[v]=cnt;
}
struct M{
	int v[125][125];
	M(){
		memset(v,0,sizeof(v));
	}
	friend void print(M a){
		for(int i=1;i<=cnt;i++)
		{
			for(int j=1;j<=cnt;j++)
				cout<<a.v[i][j]<<' ';
			cout<<endl;
		}
	}
	friend M operator*(M a,M b){
		M ans;
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++)
				for(int k=1;k<=cnt;k++)
					ans.v[i][j]=(ans.v[i][j]+a.v[i][k]*b.v[k][j])%mod;
		return ans;
	}
	friend M operator^(M a,int b){
		M ans;
		for(int i=1;i<=cnt;i++)
			ans.v[i][i]=1;
		for(int i=b;i;i>>=1,a=a*a)
			if(i&1)ans=ans*a;
		return ans;
	}
}a,b;
vector<int> q;
void build()
{
	for(int i=2;i<=cnt;i++)
		for(int j=2;j<=cnt;j++)
			if(e[i].to==e[j].from)
				if(i!=(j^1))b.v[i][j]++;
}
int main()
{
	freopen("1875.in", "r", stdin);
	n=read();m=read();t=read();A=read();B=read();
	for(int i=1;i<=m;i++)
    {
		int u=read(),v=read();
		insert(u,v);
	}
	int tot=0;
	for(int i=last[A];i;i=e[i].next) {
		a.v[1][i]++;
	}
	build();
	a=a*(b^(t-1));
	for(int i=last[B];i;i=e[i].next) {
		cout << (i ^ 1) << endl;
		tot+=a.v[1][i^1];
	}
	printf("%d\n",tot%mod);
	return 0;
}