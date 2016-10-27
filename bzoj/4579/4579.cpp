#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000005;

int n, m;
vector<int> edges[MAXN];
int que[MAXN];
int fa[MAXN];

int fin(int x) {
	int p = x, t;
	while (fa[p] != p) p = fa[p];
	while (x != p) { t = fa[x]; fa[x] = p; x = t; }
	return x;
}

void un(int a, int b) {
	fa[fin(a)] = fin(b);
}

bool vis[MAXN];
bool ans[MAXN];
int main() {
	freopen("4579.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &que[i]);
		fa[i] = i;
	}
	int cnt = 0;
	for (int i = n; i >= 1; i--) {
		int t = que[i];
		for (int j = 0; j < edges[t].size(); j++) {
			if (!vis[edges[t][j]]) continue;
			if (fin(t) != fin(edges[t][j])) {
				cnt++;
				un(t, edges[t][j]);
			}
		}
		vis[t] = 1;
		if (cnt == n - i) ans[i] = 1;
		else ans[i] = 0;
	}
	for (int i = 1; i <= n; i++)
		if (ans[i]) printf("YES\n");
		else printf("NO\n");


	return 0;
}
