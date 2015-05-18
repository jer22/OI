#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const double eps = 1e-8;
const int MAXN = 1005;
const int INF = 0x3f3f3f3f;

int n, m;
int ss, tt;
vector<int> edges[MAXN];
int deg[MAXN];
int dist[MAXN][MAXN], p[MAXN][MAXN];
bool vis[MAXN];
void spfa(int s) {
	queue<int> q;
	memset(dist[s], 0x3f, sizeof(dist[s]));
	memset(p[s], 0x3f, sizeof(p[s]));
	memset(vis, 0, sizeof(vis));
	dist[s][s] = 0;
	for (int i = 0; i < edges[s].size(); i++) {
		dist[s][edges[s][i]] = 1;
		p[s][edges[s][i]] = edges[s][i];
		q.push(edges[s][i]);
		vis[edges[s][i]] = 1;
	}
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			int nex = edges[cur][i];
			if (dist[s][cur] + 1 < dist[s][nex]) {
				dist[s][nex] = dist[s][cur] + 1;
				p[s][nex] = p[s][cur];
				if (!vis[nex]) {
					vis[nex] = 1;
					q.push(nex);
				}
			} else if (dist[s][cur] + 1 == dist[s][nex]) {
				p[s][nex] = min(p[s][nex], p[s][cur]);
				if (!vis[nex]) {
					vis[nex] = 1;
					q.push(nex);
				}
			}
		}
		vis[cur] = 0;
	}
}

double f[MAXN][MAXN];

double dfs(int s, int t) {
	if (f[s][t] > eps) return f[s][t];
	if (s == t) return f[s][t] = 0;
	if (p[s][t] == t || p[p[s][t]][t] == t) return f[s][t] = 1;
	f[s][t] = 0;
	f[s][t] = dfs(p[p[s][t]][t], t);
	for (int i = 0; i < edges[t].size(); i++) {
		f[s][t] += dfs(p[p[s][t]][t], edges[t][i]);
	}
	f[s][t] /= deg[t] + 1;
	f[s][t] += 1;
	return f[s][t];
}

int main() {
	freopen("1415.in", "r", stdin);
	scanf("%d %d", &n, &m);
	scanf("%d %d", &ss, &tt);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
		deg[a]++;
		deg[b]++;
	}
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= n; i++) {
		spfa(i);
		f[i][i] = 0;
	}
	double ans = dfs(ss, tt);
	printf("%.3lf\n", ans);

	return 0;
}
