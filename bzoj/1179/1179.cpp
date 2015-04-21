#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define INF 0x7f7f7f7f

using namespace std;

const int MAXN = 500005;

int n, m, S, p;
vector<int> orig[MAXN];
vector<int> edges[MAXN];
int money[MAXN];
bool hasbar[MAXN];
bool vis[MAXN];
int dfn[MAXN], low[MAXN], col[MAXN], tot[MAXN];
int cnt, num;
stack<int> s;

void dfs(int u) {
	s.push(u);
	vis[u] = 1;
	dfn[u] = low[u] = ++cnt;
	for (int i = 0; i < orig[u].size(); i++) {
		int v = orig[u][i];
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int t;
		num++;
		do {
			t = s.top();
			s.pop();
			vis[t] = 0;
			col[t] = num;
			tot[num] += money[t];
		} while (t != u);
	}
}

void tarjan() {
	cnt = num = 0;
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
}

void rebuild() {
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < orig[i].size(); j++)
			if (col[i] != col[orig[i][j]])
				edges[col[i]].push_back(col[orig[i][j]]);
}

int dist[MAXN];
void spfa() {
	memset(dist, 0, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[col[S]] = tot[col[S]];
	vis[col[S]] = 1;
	q.push(col[S]);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			int nex = edges[cur][i];
			if (dist[cur] + tot[nex] > dist[nex]) {
				dist[nex] = dist[cur] + tot[nex];
				if (!vis[nex]) {
					vis[nex] = 1;
					q.push(nex);
				}
			}
		}
		vis[cur] = 0;
	}
}

int main() {
	freopen("1179.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		orig[a].push_back(b);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &money[i]);
	scanf("%d %d", &S, &p);
	for (int i = 0; i < p; i++) {
		scanf("%d", &a);
		hasbar[a] = 1;
	}
	tarjan();
	rebuild();
	spfa();
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (hasbar[i]) ans = max(ans, dist[col[i]]);
	cout << ans << endl;
	return 0;
}
