#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int n, t;
int cnt = 0, num = 0;
stack<int> s;
vector<int> edges[105];
int dfn[105], low[105];
int vis[105];
int col[105];
int in[105], out[105];
int tree[105][105];

void tarjan(int u) {
	s.push(u);
	vis[u] = 1;
	dfn[u] = low[u] = ++cnt;
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		num++;
		do {
			t = s.top();
			s.pop();
			col[t] = num;
			vis[t] = 0;
		} while (t != u);
	}
}

int main() {
	freopen("1236.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		while (!s.empty()) s.pop();
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, 0, sizeof(vis));
		memset(col, 0, sizeof(col));
		memset(tree, 0, sizeof(tree));
		for (int i = 1; i <= n; i++) {
			while (cin >> t) {
				if (!t) break;
				edges[i].push_back(t);
			}
		}
		cnt = num = 0;
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) tarjan(i);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				if (col[edges[i][j]] == col[i]) continue;
				if (tree[col[i]][col[edges[i][j]]]) continue;
				tree[col[i]][col[edges[i][j]]] = 1;
				in[col[edges[i][j]]]++;
				out[col[i]]++;
			}
		}
		if (num == 1) printf("1\n0\n");
		else {
			int ans1 = 0, ans2 = 0;
			for (int i = 1; i <= num; i++) {
				if (!in[i]) ans1++;
				if (!out[i]) ans2++;
			}
			printf("%d\n%d\n", ans1, max(ans1, ans2));
		}
	}


	return 0;
}
