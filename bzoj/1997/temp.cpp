#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<cmath>
#define inf 1000000000
#define rad 100000000
#define pa pair<int,int>
#define ll long long 
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int T,n,m,ind,top,cnt,scc;
int u[10005],v[10005];
int c[2005],pos[2005];
int last[2005],dfn[2005],low[2005],q[2005],bl[2005];
bool inq[2005];
struct edge{
	int to,next;
}e[1000005];
void insert(int u,int v)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
}
void tarjan(int x)
{
	inq[x]=1;q[++top]=x;
	low[x]=dfn[x]=++ind;
	for(int i=last[x];i;i=e[i].next)
		if(!dfn[e[i].to])
			tarjan(e[i].to),low[x]=min(low[x],low[e[i].to]);
		else if(inq[e[i].to])
			low[x]=min(low[x],dfn[e[i].to]);
	int now=-1;
	if(low[x]==dfn[x])
	{
		scc++;
		while(now!=x)
		{
			now=q[top--];inq[now]=0;
			bl[now]=scc;
		}
	}
}
bool jud()
{
	for(int i=1;i<=m;i++)
		if(bl[2*i]==bl[2*i-1])return 0;
	return 1;
}
int main()
{
	freopen("1997.in", "r", stdin);
	T=read();
	while(T--)
	{
		n=read();m=read();
		for(int i=1;i<=m;i++)
			u[i]=read(),v[i]=read();
		memset(last,0,sizeof(last));cnt=0;
		scc=ind=0;
		memset(low,0,sizeof(low));
		memset(dfn,0,sizeof(dfn));
		for(int i=1;i<=n;i++)c[i]=read();
		if(m>3*n-6){puts("NO");continue;}
		for(int i=1;i<=n;i++)pos[c[i]]=i;
		top=0;
		for(int i=1;i<=m;i++)
		{
			v[i]=pos[v[i]];u[i]=pos[u[i]];
			if(u[i]>v[i])swap(u[i],v[i]);
			if(v[i]-u[i]==1||(v[i]==n&&u[i]==1))continue;
			u[++top]=u[i],v[top]=v[i];
		}
		m=top;
		for(int i=1;i<=m;i++)
			for(int j=i+1;j<=m;j++)
				if((u[i]<u[j]&&u[j]<v[i]&&v[i]<v[j])||(u[j]<u[i]&&u[i]<v[j]&&v[j]<v[i]))
				{
					insert(2*i-1,2*j);
					insert(2*i,2*j-1);
					insert(2*j-1,2*i);
					insert(2*j,2*i-1);
				}
		top=0;
		for(int i=1;i<=2*m;i++)
			if(!dfn[i])tarjan(i);
		if(jud())puts("YES");
		else puts("NO");
	}
	return 0;
}