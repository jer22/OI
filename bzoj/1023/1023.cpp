#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

#define MAXN 50005

using namespace std;

int n, m;
vector<int> edges[MAXN];
stack<int> s;
int dfn[MAXN], low[MAXN], col[MAXN], vis[MAXN];
int cnt, num;
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
		int t;
		num++;
		do{
			t = s.top();
			s.pop();
			col[t] = num;
			vis[t] = 0;
		} while (t != u);
	}
}

void tarjan() {
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
}

int main() {
	freopen("1023.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int k, x, y;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &k);
		scanf("%d", &y);
		for (int i = 2; i <= k; i++) {
			scanf("%d", &x);
			// edges[x].push_back(y);
			edges[y].push_back(x);
			y = x;
		}
	}
	tarjan();
	for (int i = 1; i <= n; i++)
		cout << col[i] << endl;
	return 0;
}
