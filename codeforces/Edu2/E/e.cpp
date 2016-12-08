#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

const int MAXN = 100005;

int n, siz[MAXN];
long long col[MAXN], mx[MAXN], ans[MAXN];
vector<int> edges[MAXN];
unordered_map<int, int> cnt[MAXN];
int dsu[MAXN], tot = 0;
void relax(int x, int mxcnt, int col) {
	if (mxcnt > mx[x]) mx[x] = mxcnt, ans[x] = col;
	else if (mxcnt == mx[x]) ans[x] += (long long)col;
}
void un(int x, int a, int b) {
	for (auto y : cnt[b])
		relax(x, cnt[a][y.first] += y.second, y.first);
}

void dfs(int x, int pre) {
	siz[x] = 1;
	if ((int)edges[x].size() == 1 && edges[x][0] == pre) {
		dsu[x] = ++tot;
		cnt[tot][col[x]] = 1;
		ans[x] = col[x];
		mx[x] = 1;
		return;
	}
	int mxson = -1;
	for (auto &nex : edges[x]) if (nex != pre) {
		dfs(nex, x);
		siz[x] += siz[nex];
		if (mxson == -1 || siz[nex] > siz[mxson]) mxson = nex;
	}
	dsu[x] = dsu[mxson];
	ans[x] = ans[mxson], mx[x] = mx[mxson];
	for (auto &nex : edges[x]) if (nex != pre && nex != mxson)
		un(x, dsu[x], dsu[nex]);
	relax(x, ++cnt[dsu[x]][col[x]], col[x]);
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &col[i]);
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 1);
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " \n"[i == n];

	return 0;
}
