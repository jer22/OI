#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

#define INF 0X3F3F3F3F
#define MAXN 505
#define S 0
#define T n + 1

using namespace std;

struct Edge{
	int to;
	int cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(S);
	layer[S] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge &e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap))) != 0) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(S, INF);
	}
	return flow;
}

int arr[MAXN], val[MAXN];
int fr[2005], to[2005];
bool vis[MAXN];

void dfs(int x) {
	vis[x] = 1;
	for (int i = 0; i < G[x].size(); i++)
		if (edges[G[x][i] ^ 1].cap && !vis[edges[G[x][i]].to])
			dfs(edges[G[x][i]].to);
}

void build_graph(int x) {
	edges.clear();
	for (int i = 0; i <= T; i++)
		G[i].clear();
	for (int i = 1; i <= n; i++) {
		if (arr[i] >= 0) {
			if (arr[i] & x) addEdge(i, T, INF);
			else addEdge(0, i, INF);
		}
	}
	for (int i = 0; i < m; i++) {
		addEdge(fr[i], to[i], 1);
		addEdge(to[i], fr[i], 1);
	}
}

int main() {
	freopen("2400.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	for (int i = 0; i < m; i++)
		scanf("%d %d", &fr[i], &to[i]);
	long long ans = 0;
	for (int i = 0; i <= 30; i++) {
		int now = 1 << i;
		build_graph(now);
		ans += (long long)dinic() * now;
		memset(vis, 0, sizeof(vis));
		dfs(T);
		for (int j = 1; j <= n; j++)
			if (vis[j]) val[j] += now;
	}
	long long res = 0;
	for (int i = 1; i <= n; i++)
		if (arr[i] >= 0) res += arr[i];
		else res += val[i];
	cout << ans << endl <<  res << endl;
	return 0;
}
