#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;

int n;
vector<int> edges[MAXN];
int w[MAXN];
int siz[MAXN], son[MAXN], fa[MAXN], top[MAXN];
int dfn[MAXN], lst[MAXN], tot = 0;
int c[2][MAXN];

void ins(int x, int v, int id) {
	for (int i = x; i <= tot; i += i & -i)
		c[id][i] += v;
}
int sum(int x, int id) {
	int ans = 0;
	for (int i = x; i; i -= i & -i)
		ans += c[id][i];
	return ans;
}

void dfs(int x, int pre) {
	siz[x] = 1;
	son[x] = 0;
	fa[x] = pre;
	for (auto nex : edges[x]) if (nex != pre) {
		dfs(nex, x);
		siz[x] += siz[nex];
		if (!son[x] || siz[nex] > siz[son[x]]) {
			son[x] = nex;
		}
	}
}

void ddffss(int x) {
	dfn[x] = ++tot;
	if (son[x]) {
		top[son[x]] = top[x];
		ddffss(son[x]);
	}
	for (auto nex : edges[x]) if (nex != fa[x] && nex != son[x]) {
		top[nex] = nex;
		ddffss(nex);
	}
	lst[x] = tot;
}

void update(int x) {
	ins(dfn[x], 1, 0);
	ins(dfn[x], w[x], 1);
	while (x) {
		x = fa[top[x]];
		if (x) ins(dfn[x], w[x], 1);
	}
}

int getans(int x) {
	int ans = 0;
	if (son[x]) ans += (sum(lst[son[x]], 0) - sum(dfn[son[x]] - 1, 0)) * w[x];
	while (x) {
		ans += sum(dfn[x], 1) - sum(dfn[top[x]] - 1, 1);
		x = top[x];
		if (fa[x]) {
			ans += (sum(lst[son[fa[x]]], 0) - sum(dfn[son[fa[x]]] - 1, 0)) * w[fa[x]];
			ans -= (sum(lst[x], 0) - sum(dfn[x] - 1, 0)) * w[fa[x]];
		}
		x = fa[x];
	}
	return ans;
}

int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &w[i]);
			edges[i].clear();
		}
		for (int i = 2, a; i <= n; i++) {
			scanf("%d", &a);
			edges[a].push_back(i);
			edges[i].push_back(a);
		}
		tot = 0;
		top[1] = 1;
		dfs(1, 0);
		ddffss(1);
		memset(c, 0, sizeof(c));

		for (int i = 2; i <= n; i++) {
			update(i - 1);
			cout << getans(i) << endl;
		}
		// cout << getans(3) << endl;
	}


	return 0;
}
