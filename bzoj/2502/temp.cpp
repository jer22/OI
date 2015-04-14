#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 1001;
const int INF = 10000001;

struct Edge
{
	int from,to,cap,flow;
};

int n,S,T,SS,ST;
int dist[MAXN],a[MAXN],cur[MAXN];
bool vis[MAXN];
vector <Edge> Edges;
vector <int> G[MAXN];

void AddEdge(int from,int to,int cap)
{
	Edges.push_back((Edge){from,to,cap,0});
	Edges.push_back((Edge){to,from,0,0});
	int m = Edges.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
}

void clear(int mid)
{
	for (int i=0;i<Edges.size();i++) Edges[i].flow = 0;
	Edges[Edges.size()-2].cap = mid;
}

bool bfs(int s,int t)
{
	memset(dist,0,sizeof(dist));
	queue <int> Q;Q.push(s);
	dist[s] = 1;
	while (!Q.empty())
	{
		int u = Q.front();Q.pop();
		for (int i=0;i<G[u].size();i++)
		{
			Edge e = Edges[G[u][i]];
			if (e.cap <= e.flow) continue;
			if (!dist[e.to])
			{
				dist[e.to] = dist[u]+1;
				Q.push(e.to);
			}
		}
	}
	return dist[t];
}

int dfs(int u,int a,int t)
{
	if (u == t || a <= 0) return a;
	int flow = 0;
	for (int &i = cur[u];i<G[u].size();i++)
	{
		Edge &e = Edges[G[u][i]];
		if (e.cap > e.flow && dist[e.to] == dist[u]+1)
		{
			int f = dfs(e.to,min(a,e.cap-e.flow),t);
			if (f <= 0) continue;
			e.flow += f;
			Edges[G[u][i]^1].flow -= f;
			flow += f;
			a -= f;
			if (a == 0) break;
		}
	}
	return flow;
}

int Dinic(int s,int t)
{
	int ans = 0;
	while (bfs(s,t))
	{
		memset(cur,0,sizeof(cur));
		ans += dfs(s,INF,t);
	}
	return ans;
}

bool check()
{
	for (int i=0;i<G[SS].size();i++) 
	{
		Edge e = Edges[G[SS][i]];
		if (e.cap > e.flow) return false;
	}
	return true;
}

int main()
{
	freopen("2502.in", "r", stdin);
	scanf("%d",&n);
	S = 0, T = n+1;
	SS = n+2, ST = n+3;
	for (int i=1;i<=n;i++)
	{
		int cnt;
		scanf("%d",&cnt);
		for (int j=1;j<=cnt;j++)
		{
			int x;
			scanf("%d",&x);
			AddEdge(i,ST,1);
			AddEdge(SS,x,1);
			AddEdge(i,x,INF);
			vis[x] = true;
		}
		if (cnt == 0) AddEdge(i,T,INF);
	}
	for (int i=1;i<=n;i++) if (!vis[i]) AddEdge(S,i,INF);
	AddEdge(T,S,INF);
	int l = 1, r = 100001;
	while (l+1 != r)
	{
		int mid = (l+r)/2;
		clear(mid);
		Dinic(SS,ST);
		if (check()) r = mid;
		else l = mid;
	}
	printf("%d\n",r);
	return 0;
}