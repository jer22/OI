#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

struct Edge{
	int from, to, v;
	Edge() {}
	Edge(int a, int b, int c) : from(a), to(b), v(c) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN];
bool vis[MAXN];
int dist[MAXN], fir[MAXN];

void spfa() {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[1] = 0;
	vis[1] = 1;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (int i = 0; i < G[cur].size(); i++) {
			Edge &e = edges[G[cur][i]];
			if (dist[e.to] > dist[cur] + e.v) {
				dist[e.to] = dist[cur] + e.v;
				fir[e.to] = (cur == 1) ? e.to : fir[cur];
				if (!vis[e.to]) q.push(e.to);
			}
		}
	}
}

vector<Edge> nes[MAXN];

int spfa2() {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[1] = 0;
	vis[1] = 1;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (int i = 0; i < nes[cur].size(); i++) {
			Edge &e = nes[cur][i];
			if (dist[e.to] > dist[cur] + e.v) {
				dist[e.to] = dist[cur] + e.v;
				if (!vis[e.to]) q.push(e.to);
			}
		}
	}
	return dist[n + 1] == 0x3f3f3f3f ? -1 : dist[n + 1];
}

int main() {
	freopen("2407.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b, c, d;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		edges.push_back(Edge(a, b, c));
		edges.push_back(Edge(b, a, d));
		G[a].push_back(edges.size() - 2);
		G[b].push_back(edges.size() - 1);
	}
	spfa();
	for (int i = 0; i < edges.size(); i++) {
		Edge e = edges[i];
		a = e.from, b = e.to;
		if (a == 1) {
			if (fir[b] != b) nes[1].push_back(Edge(1, b, e.v));
		} else if (b == 1) {
			if (fir[a] == a) nes[a].push_back(Edge(a, n + 1, e.v));
			else nes[1].push_back(Edge(1, n + 1, dist[a] + e.v));
		} else {
			if (fir[a] != fir[b]) nes[1].push_back(Edge(1, b, dist[a] + e.v));
			else nes[a].push_back(Edge(a, b, e.v));
		}
	}
	int ans = spfa2();
	printf("%d\n", ans);

	return 0;
}
