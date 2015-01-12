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

int n, m;
vector<Edge> edges[105];

void addEdge(int from, int to, int v) {
	edges[from].push_back(Edge(to, v));
}

int dist[105];
int vis[105];
int cnt[105];
bool spfa() {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	queue<int> q;
	q.push(0);
	vis[0] = cnt[0] = 1;
	dist[0] = 0;
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
					if (cnt[e.to] > n + 2)
						return false;
					q.push(e.to);
				}
			}
		}
		vis[current] = 0;
	}
	return true;
}

int main() {
	freopen("1364.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		scanf("%d", &m);
		for (int i = 0; i <= n + 2; i++)
			edges[i].clear();
		char op[5];
		int s, ni, k;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d %s %d", &s, &ni, op, &k);
			if (op[0] == 'g')
				addEdge(s + ni + 1, s, -k - 1);
			else addEdge(s, s + ni + 1, k - 1);
		}
		for (int i = 1; i <= n + 1; i++)
			addEdge(0, i, 0);
		if (!spfa()) printf("successful conspiracy\n");
		else printf("lamentable kingdom\n");
	}
	return 0;
}
