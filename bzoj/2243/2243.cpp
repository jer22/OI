#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 100005;

int n, m;
int rev[MAXN], cov[MAXN];
int tr[MAXN][2], fa[MAXN];
int q[MAXN], top = 0;
int lc[MAXN], rc[MAXN], sum[MAXN], val[MAXN];
vector<int> edges[MAXN];

void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (rev[x]) {
		rev[x] ^= 1;
		rev[l] ^= 1;
		rev[r] ^= 1;
		swap(tr[x][0], tr[x][1]);
		swap(lc[x], rc[x]);
	}
	if (~cov[x]) {
		lc[x] = rc[x] = val[x] = cov[x];
		cov[l] = cov[r] = cov[x];
		sum[x] = 1;
		cov[x] = -1;
	}
}
void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (l) pushdown(l);
	if (r) pushdown(r);
	sum[x] = sum[l] + sum[r] + 1;
	if (l && (rc[l] == val[x])) sum[x]--;
	if (r && (lc[r] == val[x])) sum[x]--;
	lc[x] = l ? lc[l] : val[x];
	rc[x] = r ? rc[r] : val[x];
}
bool isroot(int x) {
	return tr[fa[x]][0] != x && tr[fa[x]][1] != x;
}
void rotate(int x) {
	int y = fa[x], z = fa[y];
	int l, r;
	if (tr[y][0] == x) l = 0;
	else l = 1;
	r = l ^ 1;
	if (!isroot(y)) {
		if (tr[z][0] == y) tr[z][0] = x;
		else tr[z][1] = x;
	}
	fa[x] = z;
	fa[y] = x;
	fa[tr[x][r]] = y;
	tr[y][l] = tr[x][r];
	tr[x][r] = y;
	pushup(y);
	pushup(x);
}
void splay(int x) {
	top = 0;
	q[++top] = x;
	for (int i = x; !isroot(i); i = fa[i])
		q[++top] = fa[i];
	while (top) pushdown(q[top--]);
	while (!isroot(x)) {
		int y = fa[x], z = fa[y];
		if (!isroot(y)) {
			if (tr[y][0] == x ^ tr[z][0] == y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x) {
	for (int t = 0; x; t = x, x = fa[x])
		splay(x), tr[x][1] = t, pushup(x);
}
void makeroot(int x) {
	access(x);
	splay(x);
	rev[x] ^= 1;
}
void link(int x, int y) {
	makeroot(x);
	fa[x] = y;
}
void cut(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	tr[y][0] = fa[tr[y][0]] = 0;
	pushup(y);
}
int find(int x) {
	access(x);
	splay(x);
	while (tr[x][0]) x = tr[x][0];
	return x;
}
void cover(int x, int y, int c) {
	makeroot(x);
	access(y);
	splay(y);
	cov[y] = c;
}
void query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	printf("%d\n", sum[y]);
}

int main() {
	freopen("2243.in", "r", stdin);
	scanf("%d %d", &n, &m);
	memset(cov, -1, sizeof(cov));
	lc[0] = rc[0] = -INF;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
		lc[i] = rc[i] = val[i];
		sum[i] = 1;
	}
	int a, b, c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		link(a, b);
	}
	// query(1, 4);
	char op[3];
	for (int i = 0; i < m; i++) {
		scanf("%s %d %d", op, &a, &b);
		if (op[0] == 'Q') {
			query(a, b);
		} else {
			scanf("%d", &c);
			cover(a, b, c);
		}
	}

	return 0;
}
