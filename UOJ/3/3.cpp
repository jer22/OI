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
int ans[50002];
int spfa(int a) {
	if (ans[a] != 0) return ans[a];
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
	if (dist[n] == INF) ans[a] = -1;
	else ans[a] = dist[n] + a;
	return ans[a];
}

int cnt = 0;
int best = INF;
int dfs(int l, int r) {
	cnt++;
	if (cnt > 100) return 0;
	if (l > r) return 0;
	int mid = l + r >> 1;
	int temp = spfa(mid);
	if (l == r) {
		if (temp != -1) best = min(best, temp);
		return 0;
	}
	if (temp == -1) {
		dfs(mid + 1, min(r, best));
		return 0;
	}
	best = min(best, temp);
	int lef = best - (temp - mid);
	if (spfa(l) - l != spfa(mid) - mid) dfs(l, min(lef, mid));
	else {
		int t = spfa(l);
		if (t != -1) best = min(best, t);
	}
	int tt = spfa(r);
	if (tt == -1) tt = 0;
	else tt = tt - r;
	if (spfa(r) - r != spfa(mid) - mid) dfs(mid + 1, min(r, best - tt));
	return 0;
}

int main() {
	freopen("3.in", "r", stdin);
	memset(ans, 0, sizeof(ans));
	scanf("%d %d", &n, &m);
	int x, y, a, b;
	int maxa = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &x, &y, &b, &a);
		edges[x].push_back(Edge(y, a, b));
		edges[y].push_back(Edge(x, a, b));
		maxa = max(maxa, a);
	}
	dfs(1, maxa);
	if (best == INF) printf("-1\n");
	else printf("%d\n", best);
	return 0;
}
