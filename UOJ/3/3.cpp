

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int to, va, vb;
	Edge(int a, int b, int c) : to(a), va(b), vb(c) {}
};

int n, m;
vector<Edge> edges[50002];
int dist[50002];
bool vis[50002];
int q[500002];
bool spfa(int a) {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[1] = 0;
	vis[1] = 1;
	int head = 1, tail = 1;
	q[1] = 1;
	while (head <= tail) {
		int cur = q[head];
		head++;
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (e.va > a) continue;
			if (max(dist[cur], e.vb) < dist[e.to]) {
				dist[e.to] = max(dist[cur], e.vb);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					tail++;
					q[tail] = e.to;
					if (dist[q[head]] > dist[q[tail]]) {
						swap(q[head], q[tail]);
					}
				}
			}
		}
		vis[cur] = 0;
	}
	return dist[n] != INF;
}

int idx[100005];
int top = 0;
int main() {
	freopen("3.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int x, y, a, b;
	int mina = INF, maxa = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &x, &y, &a, &b);
		edges[x].push_back(Edge(y, a, b));
		edges[y].push_back(Edge(x, a, b));
		idx[top++] = a;
	}
	sort(idx, idx + top);
	int ans = INF;
	for (int i = 0; i < top; i++) {
		if (idx[i] > ans) break;
		if (i && idx[i] != idx[i - 1])
			if (spfa(idx[i])) ans = min(ans, dist[n] + idx[i]);
	}
	if (ans == INF) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}
