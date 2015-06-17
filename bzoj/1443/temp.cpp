#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define P 200
#define N 101000
#define M 501000
#define inf 0x3f3f3f3f
using namespace std;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
struct KSD
{
	int v,len,next;
}e[M];
int head[N],cnt;
inline void add(int u,int v,int len)
{
	e[++cnt].v=v;
	e[cnt].len=len;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline void Add(int u,int v,int len){add(u,v,len),add(v,u,0);}
int s,t,d[N];
queue<int>q;
bool bfs()
{
	while(!q.empty())q.pop();
	memset(d,0,sizeof d);

	int i,u,v;
	q.push(s),d[s]=1;
	while(!q.empty())
	{
		u=q.front(),q.pop();
		for(i=head[u];i;i=e[i].next)
		{
			if(!d[v=e[i].v]&&e[i].len)
			{
				d[v]=d[u]+1;
				if(v==t)return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
int dinic(int x,int flow)
{
	if(x==t)return flow;
	int remain=flow,i,v,k;
	for(i=head[x];i;i=e[i].next)
	{
		if(d[v=e[i].v]==d[x]+1&&e[i].len)
		{
			k=dinic(v,min(remain,e[i].len));
			if(!k)d[v]=0;
			e[i].len-=k,e[i^1].len+=k;
			remain-=k;
		}
	}
	return flow-remain;
}
char map[P][P];
int maxflow,n,m;
int id[P][P],idx[N],idy[N];
bool belong[N];
void build()
{
	int i,j,k;
	int x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",map[i]+1);
		for(j=1;j<=m;j++)if(map[i][j]=='.')
		{
			id[i][j]=++cnt;
			idx[cnt]=i;
			idy[cnt]=j;
		}
	}
	s=cnt+1,t=cnt+2,cnt=1;
	for(i=1;i<=n;i++)for(j=1;j<=m;j++)if(id[i][j])
	{
		maxflow++;
		if(i+j&1)
		{
			Add(s,id[i][j],1);
			belong[id[i][j]]=true;
			for(k=0;k<4;k++)
			{
				x=i+dx[k],y=j+dy[k];
				if(id[x][y])Add(id[i][j],id[x][y],1);
			}
		}
		else Add(id[i][j],t,1);
	}
}
bool vis[N];
int ans[N];
void dfs(int x,int d)
{
	int i,v;
	vis[x]=true;
	cout << belong[x] << ' ' << d << endl;
	if(belong[x]==d)ans[++cnt]=x;
	for(i=head[x];i;i=e[i].next)
		if(e[i].len==d&&!vis[v=e[i].v])
			dfs(v,d);
}
int main()
{
	freopen("1443.in","r",stdin);
	build();
	while(bfs())maxflow-=2*dinic(s,inf);
	if(!maxflow)
	{
		puts("LOSE");
		return 0;
	}
	else {
		puts("WIN");
		cnt=0;
		dfs(s,1);
		memset(vis,0,sizeof vis);
		dfs(t,0);
		sort(ans+1,ans+cnt+1);
		for(int i=1;i<=cnt;i++)if(ans[i]!=s&&ans[i]!=t)
			printf("%d %d\n",idx[ans[i]],idy[ans[i]]);
		return 0;
	}
	return 0;
}
