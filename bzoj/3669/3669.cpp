#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 50005;
const int MAXM = 100005;

int parent[MAXN];
int find(int r) { return (r == parent[r]) ? r : parent[r] = find(parent[r]); }
void un(int p, int q) { parent[find(p)] = find(q); }

int n, m;
struct Edge{
	int u, v, a, b;
	bool operator < (const Edge & e) const { return a < e.a; }
} edges[MAXM];

int val[MAXN + MAXM], mx[MAXN + MAXM];
int tr[MAXN + MAXM][2];
int fa[MAXN + MAXM];
int q[MAXN + MAXM], top = 0;
bool rev[MAXN + MAXM];
bool isroot(int x) {
	return tr[fa[x]][0] != x && tr[fa[x]][1] != x;
}
void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	mx[x] = x;
	if (val[mx[l]] > val[mx[x]]) mx[x] = mx[l];
	if (val[mx[r]] > val[mx[x]]) mx[x] = mx[r];
}
void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (rev[x]) {
		rev[x] ^= 1;
		rev[l] ^= 1;
		rev[r] ^= 1;
		swap(tr[x][0], tr[x][1]);
	}
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
	for (int i = top; i >= 1; i--)
		pushdown(q[i]);
	while (!isroot(x)) {
		int y = fa[x], z = fa[y];
		if (!isroot(y)) {
			if (tr[y][0] == x ^ tr[z][0] == y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	pushup(x);
}
void access(int x) {
	int t = 0;
	while (x) {
		splay(x);
		tr[x][1] = t;
		t = x;
		x = fa[x];
	}
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
	tr[y][0] = fa[x] = 0;
}
int query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	return mx[y];
}
void solve(int k) {
	int u = edges[k].u, v = edges[k].v, w = edges[k].b;
	int t = query(u, v);
	if (w < val[t]) {
		cut(edges[t - n].u, t);
		cut(edges[t - n].v, t);
		link(u, k + n);
		link(v, k + n);
	}
}

int main() {
	freopen("3669.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) parent[i] = i;
	for (int i = 1; i <= m; i++)
		scanf("%d %d %d %d", &edges[i].u, &edges[i].v, &edges[i].a, &edges[i].b);
	sort(edges + 1, edges + m + 1);
	for (int i = 1; i <= m; i++) {
		val[n + i] = edges[i].b;
		mx[n + i] = n + i;
	}
	int ans = INF;
	for (int i = 1; i <= m; i++) {
		int u = edges[i].u, v = edges[i].v;
		if (find(u) != find(v)) {
			un(u, v);
			link(u, n + i);
			link(v, n + i);
		} else solve(i);
		if (find(1) == find(n)) ans = min(ans, val[query(1, n)] + edges[i].a);
	}
	if (ans == INF) cout << -1 << endl;
	else cout << ans << endl;
	return 0;
}
