#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 200005;
const int INF = 0x3f3f3f3f;

int n, m, id = 0;

int v[MAXN], siz[MAXN], fa[MAXN];
int pos[MAXN], mx[MAXN], belong[MAXN];
vector<int> edges[MAXN];

void dfs_siz(int x) {
	siz[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != fa[x]) {
			fa[nex] = x;
			dfs_siz(nex);
			siz[x] += siz[nex];
		}
	}
}

void dfs_mark(int x, int ff) {
	belong[x] = ff;
	pos[x] = mx[x] = ++id;
	int k = 0;
	for (int i = 0; i < edges[x].size(); i++)
		if (edges[x][i] != fa[x] && siz[edges[x][i]] > siz[k])
			k = edges[x][i];
	if (k) dfs_mark(k, ff);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != fa[x] && nex != k)
			dfs_mark(nex, nex);
		mx[x] = max(mx[x], mx[nex]);
	}
}

long long sum[MAXN << 2], tag[MAXN << 2];
void pushdown(int l, int r, int rt) {
	int mid = l + r >> 1;
	if (tag[rt]) {
		tag[lch] += tag[rt];
		tag[rch] += tag[rt];
		sum[lch] += tag[rt] * (long long)(mid - l + 1);
		sum[rch] += tag[rt] * (long long)(r - mid);
		tag[rt] = 0;
	}
}

void add(int l, int r, int rt, int L, int R, long long val) {
	if (tag[rt]) pushdown(l, r, rt);
	if (l == L && r == R) {
		tag[rt] += val;
		sum[rt] += (long long)(r - l + 1) * val;
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add(lson, L, min(mid, R), val);
	if (R > mid) add(rson, max(mid + 1, L), R, val);
	sum[rt] = sum[lch] + sum[rch];
}

long long query(int l, int r, int rt, int L, int R) {
	if (tag[rt]) pushdown(l, r, rt);
	if (l == L && r == R) return sum[rt];
	int mid = l + r >> 1;
	long long ans = 0;
	if (L <= mid) ans += query(lson, L, min(mid, R));
	if (R > mid) ans += query(rson, max(mid + 1, L), R);
	return ans;
}

long long fuck(int x) {
	long long ans = 0;
	while (belong[x] != 1) {
		ans += query(1, n, 1, pos[belong[x]], pos[x]);
		x = fa[belong[x]];
	}
	ans += query(1, n, 1, 1, pos[x]);
	return ans;
}

int main() {
	freopen("4034.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &v[i]);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs_siz(1);
	dfs_mark(1, 1);
	for (int i = 1; i <= n; i++)
		add(1, n, 1, pos[i], pos[i], v[i]);
	int op, x, y;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &op, &x);
		if (op == 1) {
			scanf("%d", &y);
			add(1, n, 1, pos[x], pos[x], y);
		} else if (op == 2) {
			scanf("%d", &y);
			add(1, n, 1, pos[x], mx[x], y);
		} else {
			printf("%lld\n", fuck(x));
		}
	}

	return 0;
}
