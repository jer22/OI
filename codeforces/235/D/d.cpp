#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;

int n;
int deg[MAXN];
vector<int> edges[MAXN];
double ans = 0;
int vis[MAXN];
int dist[MAXN], dist2[MAXN];
int cirsiz = 0;

void dfs(int x) {
	vis[x] = 1;
	for (auto nex : edges[x]) if (!vis[nex]) {
		dist2[nex] = dist2[x] + 1;
		if (!dist[nex]) {
			dist[nex] = dist[x] + 1;
			ans += 1. / dist[nex];
		} else {
			ans += 1. / dist2[nex] - 2. / (dist[nex] + dist2[nex] + cirsiz - 2);
		}
		dfs(nex);
	}
	vis[x] = 0;
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1, a, b; i <= n; i++) {
		scanf("%d %d", &a, &b);
		edges[++a].push_back(++b);
		edges[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	queue<int> q;
	for (int i = 1; i <= n; ++i)
		if (deg[i] == 1) q.push(i), ++cirsiz;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (auto nex : edges[cur])
			if (--deg[nex] == 1) q.push(nex), ++cirsiz;
	}
	cirsiz = n - cirsiz;

	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		memset(dist, 0, sizeof(dist));
		memset(dist2, 0, sizeof(dist2));
		dist[i] = dist2[i] = 1;
		dfs(i);
	}
	printf("%.10lf\n", ans + n);

	return 0;
}
