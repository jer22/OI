#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 300005;

int n, m;
int rev[MAXN], tag[MAXN];
int tr[MAXN][2], fa[MAXN];
int q[MAXN], top = 0;
int val[MAXN], mx[MAXN];
vector<int> edges[MAXN];

void dfs_fa(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs_fa(nex, x);
		fa[nex] = x;
	}
}

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	mx[x] = max(max(mx[l], mx[r]), val[x]);
}
void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (rev[x]) {
		rev[x] ^= 1;
		rev[l] ^= 1;
		rev[r] ^= 1;
		swap(tr[x][0], tr[x][1]);
	}
	if (tag[x]) {
		if (l) {
			tag[l] += tag[x];
			mx[l] += tag[x];
			val[l] += tag[x];
		}
		if (r) {
			tag[r] += tag[x];
			mx[r] += tag[x];
			val[r] += tag[x];
		}
		tag[x] = 0;
	}
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
void add(int x, int y, int v) {
	makeroot(x);
	access(y);
	splay(y);
	tag[y] += v;
	val[y] += v;
	mx[y] += v;
}
void query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	cout << mx[y] << endl;
}

int main() {
	freopen("4010.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 0; i <= n; i++) {
			rev[i] = tag[i] = tr[i][0] = tr[i][1] = fa[i] = 0;
			edges[i].clear();
		}
		int a, b;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &val[i]);
			mx[i] = val[i];
		}
		dfs_fa(1, 1);
		scanf("%d", &m);
		int op;
		int x, y, z;
		for (int i = 0; i < m; i++) {
			scanf("%d", &op);
			scanf("%d %d", &x, &y);
			if (op == 1) {
				if (find(x) == find(y)) cout << -1 << endl;
				else link(x, y);
			} else if (op == 2) {
				if (find(x) != find(y) || x == y) cout << -1 << endl;
				else cut(x, y);
			} else if (op == 3) {
				scanf("%d", &z);
				if (find(y) != find(z)) cout << -1 << endl;
				else add(y, z, x	);
			} else {
				if (find(x) != find(y)) cout << -1 << endl;
				else query(x, y);
			}
		}
		cout << endl;
	}
	return 0;
}
