#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 10005;

int T, n;
int e[MAXN][3];
vector<int> edges[MAXN << 1];
int fa[MAXN << 1];
int tr[MAXN << 1][2];
int v[MAXN << 1], mx[MAXN << 1];
int q[MAXN << 1], top = 0;
bool rev[MAXN << 1];

void dfs_fa(int x) {
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == fa[x]) continue;
		fa[nex] = x;
		dfs_fa(nex);
	}
}

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	mx[x] = max(max(mx[l], mx[r]), v[x]);
}
void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (rev[x]) {
		rev[x] ^= 1, rev[l] ^= 1, rev[r] ^= 1;
		swap(tr[x][0], tr[x][1]);
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
int find(int x) {
	access(x);
	splay(x);
	while (tr[x][0]) x = tr[x][0];
	return x;
}
void change(int x, int val) {
	// makeroot(x);
	// access(x);
	splay(x);
	v[x] = val;
	pushup(x);
	// mx[x] = val;
}
void query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	printf("%d\n", mx[y]);
}

int main() {
	freopen("qtree.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n << 1; i++)
			edges[i].clear();
		for (int i = 0; i <= n << 1; i++) {
			v[i] = mx[i] = -INF;
			fa[i] = rev[i] = tr[i][0] = tr[i][1] = 0;
		}
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &e[i][0], &e[i][1], &e[i][2]);
			change(n + i, e[i][2]);
			link(e[i][0], n + i);
			link(e[i][1], n + i);
		}
		

		char op[10];
		int a, b;
		while (~scanf("%s", op)) {
			if (op[0] == 'D') break;
			scanf("%d %d", &a, &b);
			if (op[0] == 'C') {
				change(a + n, b);
			} else {
				query(a, b);
			}
		}
	}


	return 0;
}
