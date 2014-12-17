#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int to, value;
	Edge(int a, int b) : to(a), value(b) {}
};

int T;
int n, m, s, k;
char str[1111];
vector<Edge> edges[1111];
int ans[1111];
int dist[1111][1111];
void addEdge(int from, int to, int value) {
	edges[from].push_back(Edge(to, value));
}

void dfs(int v, int now) {
	if (str[v - 1] == 'P' && !(now % k)) {
		ans[v] = min(now, ans[v]);
		return;
	}
	if (ans[v] != INF) return;
	for (int i = 0; i < edges[v].size(); i++) {
		Edge e = edges[v][i];
		int nex = e.value + now;
		if ((!dist[e.to][nex % k]) || nex < dist[e.to][nex % k]) {
			dist[e.to][nex % k] = nex;
			dfs(e.to, nex);
		}
	}
}

int main() {
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		printf("Case %d: ", cas++);
		scanf("%d %d %d %d", &n, &m, &s, &k);
		scanf("%s", str);
		memset(dist, 0, sizeof(dist));
		for (int i = 0; i <= n; i++) {
			ans[i] = INF;
			edges[i].clear();
		}
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			addEdge(a, b, c);
		}
		dfs(s, 0);
		int minans = INF;
		int idx;
		for (int i = 1; i <= n; i++) {
			if (ans[i] < minans) {
				idx = i;
				minans = ans[i];
			}
		}
		if (minans != INF) printf("%d %d\n", minans, idx);
		else printf("-1 -1\n");
	}

	return 0;
}
