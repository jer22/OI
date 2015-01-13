#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
	int to, v;
	Edge(int a, int b) : to(a), v(b) {}
};

int T, n;
int r[28];
int t[28];
vector<Edge> edges[28];

void addEdge(int from, int to, int v) {
	edges[from].push_back(Edge(to, v));
}

void buildGraph(int x) {
	for (int i = 0; i <= 25; i++)
		edges[i].clear();
	for (int i = 1; i <= 24; i++) {
		addEdge(i - 1, i, t[i]);
		addEdge(i, i - 1, 0);
	}
	for (int i = 1; i <= 16; i++)
		addEdge(i + 8, i, -r[i + 8]);
	for (int i = 17; i <= 24; i++)
		addEdge(i - 16, i, x - r[i - 16]);
	addEdge(24, 0, -x);
}

int dist[28];
int vis[28];
int cnt[28];
bool spfa() {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	vis[0] = 1;
	cnt[0] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (dist[current] + e.v < dist[e.to]) {
				dist[e.to] = dist[current] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					cnt[e.to]++;
					if (cnt[e.to] > 25) {
						return 0;
					}
					q.push(e.to);
				}
			}
		}
		vis[current] = 0;
	}
	return 1;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		for (int i = 1; i <= 24; i++)
			scanf("%d", &r[i]);
		scanf("%d", &n);
		int x;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			t[x + 1]++;
		}
		int ans = -1;
		for (int i = 0; i <= n; i++) {
			buildGraph(i);
			if (spfa()) {
				ans = i;
				break;
			}
		}
		if (ans == -1) printf("No Solution\n");
		else printf("%d\n", ans);
	}
	return 0;
}
