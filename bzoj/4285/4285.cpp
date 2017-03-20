#include <bits/stdc++.h>

#define lowbit(x)  ((x) & (-(x)))

using namespace std;

const int MAXN = 100005;

int T, n, m, q;
vector<int> edges[MAXN];
int dep[MAXN], st[MAXN], ed[MAXN], tot = 0;
int fa[MAXN][22];

void dfs(int x, int pre) {
	st[x] = ++tot;
	dep[x] = dep[pre] + 1;
	fa[x][0] = pre;
	for (int i = 1; i <= 17; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x);
	}
	ed[x] = tot;
}

int getfa(int a, int t) {
	for (int i = 0; i <= 17; i++)
		if (t >> i & 1) a = fa[a][i];
	return a;
}

int getlca(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	int t = dep[a] - dep[b];
	a = getfa(a, t);
	for (int i = 17; i >= 0; i--)
		if (fa[a][i] != fa[b][i]) a = fa[a][i], b = fa[b][i];
	if (a != b) a = fa[a][0];
	return a;
}

int root[MAXN], tr[20000000][2], sum[20000000], cnt = 0;

int ins(int x, int p, int v) {
	if(!x)x=++cnt;
	sum[x] += v;
	int tmp=x;
	int l=1,r=n;
	while(l!=r)
	{
		int mid=(l+r)>>1,t=0;
		if(p>mid)t^=1,l=mid+1;
		else r=mid;
		if(!tr[x][t])tr[x][t]=++cnt;
		x=tr[x][t];sum[x]+=v;
	}
	return tmp;
}

void insert(int x, int p, int val) {
	for (int i = x; i <= n; i += lowbit(i))
		root[i] = ins(root[i], p, val);
}

int que(int x, int l, int r, int L, int R) {
	if (L <= l && r <= R) return sum[x];
	int mid = l + r >> 1;
	int ans = 0;
	if (L <= mid) ans += que(tr[x][0], l, mid, L, R);
	if (R > mid) ans += que(tr[x][1], mid + 1, r, L, R);
	return ans;
}

int query(int x, int l, int r) {
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		ans += que(root[i], 1, n, l, r);
	return ans;
}

int main() {
	freopen("4285.in", "r", stdin);
	scanf("%d", &n);
	int op, a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 0);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		insert(st[a], st[b], 1);
		insert(st[b], st[a], 1);
	}
	scanf("%d", &q);
	while (q--) {
		scanf("%d %d %d", &op, &a, &b);
		if (op == 1) {
			insert(st[a], st[b], 1);
			insert(st[b], st[a], 1);
		} else if (op == 2) {
			insert(st[a], st[b], -1);
			insert(st[b], st[a], -1);
		} else {
			int lca = getlca(a, b);
			if (lca == a || lca == b) {
				if (lca == a) swap(a, b);
				int x = getfa(a, dep[a] - dep[b] - 1);
				printf("%d\n", query(ed[a], 1, n) - query(st[a] - 1, 1, n) - (query(ed[a], st[x], ed[x]) - query(st[a] - 1, st[x], ed[x])));
			} else {
				printf("%d\n", query(ed[a], st[b], ed[b]) - query(st[a] - 1, st[b], ed[b]));
			}
		}
	}

	return 0;
}
