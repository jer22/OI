#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXN 100005

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int T;
int n, m, k;
vector<Edge> edges[MAXN];
long long dist[MAXN];
int last[MAXN];
bool vis[MAXN];
long long spfa() {
	memset(dist, -1, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	memset(last, -1, sizeof(last));
	dist[1] = 0;
	vis[1] = 1;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (last[current] != -1 && e.v - last[current] < k) continue;
			if (dist[e.to] == -1 || dist[current] + e.v < dist[e.to]) {
				dist[e.to] = dist[current] + (long long)e.v;
				last[e.to] = e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[current] = 0;
	}
	return dist[n];
}

int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
		}
		long long ans = spfa();
		printf("%lld\n", ans);
	}
	return 0;
}
