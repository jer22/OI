#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int T, n, q;
vector<int> edges[MAXN];
int col[MAXN];
int dep[MAXN], st[MAXN], ed[MAXN], tot;
int fa[MAXN][22];

void dfs(int x) {
	st[x] = ++tot;
	dep[x] = dep[fa[x][0]] + 1;
	for (int i = 1; i <= 17; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		fa[nex][0] = x;
		dfs(nex);
	}
	ed[x] = tot;
}

int getlca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	int t = dep[a] - dep[b];
	for (int i = 0; i <= 17; i++)
		if (t >> i & 1) a = fa[a][i];
	for (int i = 17; i >= 0; i--)
		if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
	if (a != b) a = fa[a][0];
	return a;
}

int root[MAXN], ls[8000000], rs[8000000], siz[8000000], cnt = 0;
void insert(int x, int &y, int l, int r, int p, int v) {
	y = ++cnt;
	siz[y] = siz[x] + v;
	if (l == r) return;
	ls[y] = ls[x], rs[y] = rs[x];
	int mid = l + r >> 1;
	if (p <= mid) insert(ls[x], ls[y], l, mid, p, v);
	else insert(rs[x], rs[y], mid + 1, r, p, v);
}
int query(int x, int l, int r, int L, int R) {
	if (L <= l && r <= R) return siz[x];
	int mid = l + r >> 1;
	int ans = 0;
	if (L <= mid) ans += query(ls[x], l, mid, L, R);
	if (R > mid) ans += query(rs[x], mid + 1, r, L, R);
	return ans;
}

set<pair<int, int> > s[MAXN];
int mx = 0;
void bfs() {
	queue<int> q;
	q.push(1);
	int lst = 0;
	mx = 0;
	for (int i = 1; i <= n; i++)
		s[i].clear();
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < edges[x].size(); i++)
			q.push(edges[x][i]);
		int cur = dep[x];
		mx = max(mx, cur);
		if (cur != lst) root[cur] = root[cur - 1], lst = cur;
		insert(root[cur], root[cur], 1, n, st[x], 1);
		s[col[x]].insert(make_pair(st[x], x));
		set<pair<int, int> >::iterator it = s[col[x]].find(make_pair(st[x], x));
		int ll = 0, rr = 0;
		if (it != s[col[x]].begin()) ll = (--it) -> second, it++;
		if ((++it) != s[col[x]].end()) rr = it -> second, it--;
		if (ll) insert(root[cur], root[cur], 1, n, st[getlca(ll, x)], -1);
		if (rr) insert(root[cur], root[cur], 1, n, st[getlca(rr, x)], -1);
		if (ll && rr) insert(root[cur], root[cur], 1, n, st[getlca(ll, rr)], 1);
	}
}

int main() {
	freopen("4771.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &q);
		tot = cnt = 0;

		for (int i = 1; i <= n; i++) {
			edges[i].clear();
		}
		for (int i = 1; i <= n; i++)
			scanf("%d", &col[i]);
		for (int i = 2, x; i <= n; i++) {
			scanf("%d", &x);
			edges[x].push_back(i);
		}
		dfs(1);
		bfs();
		int x, d;
		int lst = 0;
		while (q--) {
			scanf("%d %d", &x, &d);
			x ^= lst, d ^= lst;
			int ans = query(root[min(dep[x] + d, mx)], 1, n, st[x], ed[x]);
			printf("%d\n", ans);
			lst = ans;
		}

	}


	return 0;
}
