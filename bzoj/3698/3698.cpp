#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define S n + n + 1
#define T n + n + 2
#define SS n + n + 3
#define TT n + n + 4
#define INF 0x3f3f3f3f
#define MAXN 105
#define insert(s, t, c) deg[s] -= c, deg[t] += c;

using namespace std;

struct Edge{
	int from, to, cap, flow;
	Edge() {}
	Edge(int a, int b, int c, int d) : from(a), to(b), cap(c), flow(d) {}
};

int n, tot;
double arr[MAXN][MAXN];
vector<Edge> edges;
vector<int> G[MAXN << 1];
int deg[MAXN << 1];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(from, to, cap, 0));
	edges.push_back(Edge(to, from, 0, 0));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}


int cur[MAXN << 1], layer[MAXN << 1];
bool build(int s, int t) {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(s);
	layer[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			Edge e = edges[G[u][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[u] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[t] != -1;
}

int find(int x, int t, int a) {
	if (x == t || !a) return a;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to] && (f = find(e.to, t, min(a, e.cap - e.flow)))) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic(int s, int t) {
	int ans = 0;
	while (build(s, t)) {
		memset(cur, 0, sizeof(cur));
		ans += find(s, t, INF);
	}
	return ans;
}

int main() {
	freopen("3698.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lf", &arr[i][j]);
	for (int i = 1; i < n; i++) {
		if (arr[i][n] != (int)arr[i][n])
			addEdge(S, i, 1);
		if (arr[n][i] != (int)arr[n][i])
			addEdge(i + n, T, 1);
		insert(S, i, (int)arr[i][n]);
		insert(i + n, T, (int)arr[n][i]);
		for (int j = 1; j < n; j++) {
			if (arr[i][j] != (int)arr[i][j])
				addEdge(i, j + n, 1);
			insert(i, j + n, (int)arr[i][j]);
		}
	}
	for (int i = 1; i <= TT; i++) {
		if (deg[i] > 0) addEdge(SS, i, deg[i]), tot += deg[i];
		else addEdge(i, TT, -deg[i]);
	}
	addEdge(T, S, INF);
	if (dinic(SS, TT) != tot) printf("No\n");
	else printf("%d\n", dinic(S, T) * 3);
	return 0;
}
