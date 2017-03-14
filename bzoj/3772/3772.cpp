#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> edges[MAXN];
vector<int> pat[MAXN];
int st[MAXN], ed[MAXN], tot = 0;
int fa[MAXN][17], deep[MAXN];

int getlca(int a, int b) {
	if (deep[a] < deep[b]) swap(a, b);
	int t = deep[a] - deep[b];
	for (int i = 0; i <= 16; i++)
		if (t >> i & 1) a = fa[a][i];
	for (int i = 16; i >= 0; i--)
		if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
	if (a != b) a = fa[a][0];
	return a;
}

void dfs(int x, int pre) {
	st[x] = ++tot;
	fa[x][0] = pre;
	deep[x] = deep[pre] + 1;
	for (int j = 1; j <= 16; j++)
		fa[x][j] = fa[fa[x][j - 1]][j - 1];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != pre)
			dfs(nex, x);
	}
	ed[x] = ++tot;
}

int root[200005], ls[3800005], rs[3800005], siz[3800005], cnt = 0;
void insert(int x, int &y, int l, int r, int pos, int v) {
	y = ++cnt;
	siz[y] = siz[x] + v;
	if (l == r) return;
	ls[y] = ls[x], rs[y] = rs[x];
	int mid = l + r >> 1;
	if (pos <= mid) insert(ls[x], ls[y], l, mid, pos, v);
	else insert(rs[x], rs[y], mid + 1, r, pos, v);
}
void sfd(int x, int pre) {
	root[x] = root[fa[x][0]];
	for (int i = 0; i < pat[x].size(); i++) {
		int p = pat[x][i];
		insert(root[x], root[x], 1, tot, st[p], 1);
		insert(root[x], root[x], 1, tot, ed[p], -1);
	}
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != pre)
			sfd(nex, x);
	}
}
int query(int a, int b, int c, int d, int l, int r, int L, int R) {
	if (L <= l && r <= R) return siz[a] + siz[b] - siz[c] - siz[d];
	int mid = l + r >> 1;
	long long ans = 0;
	if (mid >= L) ans += query(ls[a], ls[b], ls[c], ls[d], l, mid, L, R);
	if (mid < R) ans += query(rs[a], rs[b], rs[c], rs[d], mid + 1, r, L, R);
	return ans;
}

pair<int, int> que[MAXN];
int main() {
	freopen("3772.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		pat[a].push_back(b);
		que[i] = {a, b};
	}
	dfs(1, 0);
	sfd(1, 0);
	long long ans = 0;
	for (int i = 0; i < m; i++) {
		a = que[i].first, b = que[i].second;
		int lca = getlca(a, b);
		ans += query(root[a], root[b], root[lca], root[fa[lca][0]], 1, tot, st[lca], st[a]);
		ans += query(root[a], root[b], root[lca], root[fa[lca][0]], 1, tot, st[lca], st[b]);
		ans -= query(root[a], root[b], root[lca], root[fa[lca][0]], 1, tot, st[lca], st[lca]);
		ans--;
	}
	sort(que, que + m);
	for (int i = 0, j; i < m; i = j) {
		for (j = i + 1; j < m && que[i] == que[j]; j++);
		ans -= (long long)(j - i) * (j - i - 1) >> 1;
	}
	long long f = (long long)m * (m - 1) >> 1ll;
	long long gcd = __gcd(ans, f);
	ans /= gcd, f /= gcd;
	printf("%lld/%lld\n", ans, f);

	return 0;
}
