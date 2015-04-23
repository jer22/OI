#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int n, m;
vector<Edge> edges[1005];
long long dist[1005];
bool vis[1005];

void spfa() {
	for (int i = 0; i <= n; i++)
		dist[i] = 1000000000000000000;
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	vis[0] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (dist[cur] + e.v < dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
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
	freopen("c.in", "r", stdin);
	long long x0, x1, y0, y1;
	while (cin >> n >> m >> x0 >> x1 >> y0 >> y1) {
		for (int i = 0; i < 1002; i++)
			edges[i].clear();
		long long z1 = (x1 * 90123 + y1) % 8475871 + 1;
		edges[0].push_back(Edge(1, z1));
		for (int k = 2; k < n * n; k++) {
			long long x = ((12345 + x1 * 23456 + x0 * 34567) % 5837501 + ((x1 * x0) % 5837501) * 45678) % 5837501;
			long long y = ((56789 + y1 * 67890 + y0 * 78901) % 9860381 + ((y1 * y0) % 9860381) * 89012) % 9860381; 
			long long z = (x * 90123 + y) % 8475871 + 1;
			int i = k / n, j = k % n;
			long long v = 0;
			if (i != j) edges[i].push_back(Edge(j, z));
			x0 = x1, x1 = x;
			y0 = y1, y1 = y;
		}
		spfa();
		int ans = 0x3f3f3f3f;
		for (int i = 1; i < n; i++) {
			int t = dist[i] % m;
			ans = min(ans, t);
		}
		printf("%d\n", ans);
	}
	return 0;
}
