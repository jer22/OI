/* copy */

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<deque>
#include<set>
#include<map>
#include<string>
#define make make_pair
#define fi first
#define se second

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int maxn=100010;
const int maxm=1010;
const int maxs=26;
const int INF=1<<29;
const int P=1000000007;
const double error=1e-9;

struct edge{ int v,a,next; }e[30*maxn];

int s,t,n,m,cnt=0,ans=0,head[maxn],dis[maxn],cur[maxn],q[maxn];

void addedge(int u,int v,int a)
{
	e[cnt]=(edge){v,a,head[u]},head[u]=cnt++;
	e[cnt]=(edge){u,0,head[v]},head[v]=cnt++;
}

bool bfs()
{
	memset(dis,-1,sizeof(dis));
	int he=1,ta=1;dis[q[1]=s]=0;
	
	while(he<=ta)
	{
		int u=q[he++];
		for(int i=head[u],v;i!=-1;i=e[i].next)
			if(e[i].a&&dis[v=e[i].v]==-1) dis[v]=dis[u]+1,q[++ta]=v;
	}
	return dis[t]!=-1;
}

int dfs(int u,int a)
{
	if(u==t) return a;
	int f,flow=0;
	for(int i=cur[u];a&&i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		if(e[i].a&&dis[v]==dis[u]+1&&(f=dfs(v,min(a,e[i].a)))>0)
		{
			e[i].a-=f,e[i^1].a+=f,a-=f,flow+=f;
			if(e[i].a) cur[u]=i;
		}
	}
	if(!flow) dis[u]=-1;
	return flow;
}

void dinic()
{
	while(bfs()) memcpy(cur,head,sizeof(head)),ans-=dfs(s,INF);
}

int main()
{
	scanf("%d%d",&n,&m);
	s=n+m+1;t=n+m+2;
	
	memset(head,-1,sizeof(head));
	for(int i=1,w,x;i<=n;i++)
	{
		 scanf("%d%d",&w,&x);
		 addedge(s,i,w);ans+=w;
		 for(int j=1,a,b;j<=x;j++) scanf("%d%d",&a,&b),addedge(i,n+a,b);
	}
	
	for(int i=1,w;i<=m;i++) scanf("%d",&w),addedge(n+i,t,w);
	
	dinic();printf("%d\n",ans);

	return 0;
}