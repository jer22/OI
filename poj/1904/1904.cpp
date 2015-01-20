#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int n, t;
vector<int> edges[4005];
vector<int> ans[4005];
int dfn[4005], low[4005];
int vis[4005], col[4005];
stack<int> s;
int cnt = 0, num = 0;
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
	while (~scanf("%d", &n)) {
		int k, a;
		for (int i = 0; i <= n; i++) {
			edges[i].clear();
			ans[i].clear();
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {
				scanf("%d", &a);
				edges[i].push_back(a + n);
			}
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a);
			edges[a + n].push_back(i);
		}
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, 0, sizeof(vis));
		memset(col, 0, sizeof(col));
		while (!s.empty()) s.pop();
		cnt = num = 0;
		for (int i = 1; i <= n; i++)
			if (!dfn[i]) tarjan(i);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				if (col[i] == col[edges[i][j]])
					ans[i].push_back(edges[i][j] - n);
			}
			sort(ans[i].begin(), ans[i].end());
		}
		for (int i = 1; i <= n; i++) {
			int siz = ans[i].size();
			printf("%d", siz);
			for (int j = 0; j < siz; j++) {
				printf(" %d", ans[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
