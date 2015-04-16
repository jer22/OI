#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000000000000

using namespace std;

struct Edge{
	int to;
	long long cap;
	Edge() {}
	Edge(int a, long long b) : to(a), cap(b) {}
};

int n, m;
vector<Edge> ee[505];
vector<Edge> pre[505];
long long dist[505];
bool vis[505];
vector<Edge> edges;
vector<int> G[1005];
long long cc[505];

void addEdge(int from, int to, long long cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	int E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
}

int layer[1005], cur[1005];
int S, T;
bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(S);
	layer[S] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > 0) { // 只考虑残量网络中的弧
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

long long find(int x, long long a) {
	if (x == T || a == 0) return a;
	long long flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
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

long long dinic(int s, int t) {
	S = s, T = t;
	long long flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(s, INF);
	}
	return flow;
}

void build_graph() {
	cc[1] = cc[n] = INF;
	for (int i = 1; i <= n; i++)
		addEdge(i, i + n, cc[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < pre[i].size(); j++) {
			Edge e = pre[i][j];
			addEdge(i + n, e.to, INF);
		}
	}
}

void spfa() {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	dist[1] = 0;
	vis[1] = 1;
	q.push(1);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < ee[cur].size(); i++) {
			Edge e = ee[cur][i];
			if (dist[cur] + e.cap == dist[e.to]) {
				pre[e.to].push_back(Edge(cur, e.cap));
			} else if (dist[cur] + e.cap < dist[e.to]) {
				dist[e.to] = dist[cur] + e.cap;
				pre[e.to].clear();
				pre[e.to].push_back(Edge(cur, e.cap));
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
}

int main() {
	freopen("3931.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		ee[a].push_back(Edge(b, c));
		ee[b].push_back(Edge(a, c));
	}
	for (int i = 1; i <= n; i++)
		scanf("%lld", &cc[i]);
	spfa();
	build_graph();
	cout << dinic(n, 1 + n) << endl;
	return 0;
}
