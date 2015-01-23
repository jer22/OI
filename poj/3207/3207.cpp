#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

struct Pair{
	int x, y;
	Pair() {}
	Pair(int a, int b) : x(a), y(b) {}
};

int n, m, t;
int cnt, num;
vector<int> edges[1002];
Pair p[502];
stack<int> s;
int dfn[1002];
int low[1002];
int vis[1002];
int col[1005];

void dfs(int u) {
	s.push(u);
	vis[u] = 1;
	dfn[u] = low[u] = ++cnt;
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		num++;
		do {
			t = s.top();
			s.pop();
			vis[t] = 0;
			col[t] = num;
		} while (t != u);
	}
}

void tarjan() {
	cnt = num = 0;
	while (!s.empty()) s.pop();
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(col, 0, sizeof(col));
	for (int i = 1; i <= m << 1; i++)
		if (!dfn[i]) dfs(i);
}

bool solve() {
	tarjan();
	for (int i = 1; i <= m; i++)
		if (col[i] == col[i + m]) return false;
	return true;
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= m << 1; i++)
			edges[i].clear();
		int a, b;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &a, &b);
			if (a > b) swap(a, b);
			p[i] = Pair(a, b);
		}
		for (int i = 1; i <= m; i++) {
			for (int j = i + 1; j <= m; j++) {
				if (p[j].x >= p[i].x && p[j].x <= p[i].y && p[j].y >= p[i].y
					|| p[j].y >= p[i].x && p[j].y <= p[i].y && p[j].x <= p[i].x) {
					edges[i].push_back(j + m);
					edges[j].push_back(i + m);
					edges[i + m].push_back(j);
					edges[j + m].push_back(i);
				}
			}
		}
		bool ans = solve();
		if (ans) printf("panda is telling the truth...\n");
		else printf("the evil panda is lying again");
	}
	return 0;
}
