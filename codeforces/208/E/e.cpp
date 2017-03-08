#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> edges[MAXN];
int siz[MAXN], maxson[MAXN], fa[MAXN][22], deep[MAXN];
int ans[MAXN];
vector<pair<int, int> > que[MAXN];

int getfa(int x, int k) {
	for (int i = 0; i <= 20; i++)
		if ((k >> i) & 1) x = fa[x][i];
	return x;
}

void dfspre(int x) {
	deep[x] = deep[fa[x][0]] + 1;
	siz[x] = 1;
	for (int j = 1; j <= 20; j++)
		fa[x][j] = fa[fa[x][j - 1]][j - 1];
	for (auto nex : edges[x]) {
		fa[nex][0] = x;
		dfspre(nex);
		siz[x] += siz[nex];
		if (siz[nex] > siz[maxson[x]])
			maxson[x] = nex;
	}
}

int cnt[MAXN];
void fuck(int x, int ban, int f) {
	cnt[deep[x]] += f;
	for (auto nex : edges[x])
		if (nex != ban) fuck(nex, ban, f);
}

void dfs(int x, bool keep) {
	for (auto nex : edges[x])
		if (nex != maxson[x]) dfs(nex, 0);
	if (maxson[x]) dfs(maxson[x], 1);

	fuck(x, maxson[x], 1);
	for (auto q : que[x]) {
		ans[q.second] = cnt[q.first + deep[x]] - 1;
	}
	if (!keep) fuck(x, 0, -1);
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		edges[x].push_back(i);
	}
	dfspre(0);
	scanf("%d", &m);
	for (int i = 0, a, b; i < m; i++) {
		scanf("%d %d", &a, &b);
		int p = getfa(a, b);
		if (p) que[p].push_back({b, i});
	}
	dfs(0, 0);
	for (int i = 0; i < m; i++) {
		cout << ans[i] << endl;
	}

	return 0;
}
