#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 30005;

int n, m;
vector<int> edges[MAXN];
int rev[MAXN], fa[MAXN], tr[MAXN][2];
int q[MAXN], top = 0;
int val[MAXN], mx[MAXN], sum[MAXN];

void dfs_fa(int x) {
	for (int i = 0; i < edges[x].size(); i++) {
		if (edges[x][i] != fa[x]) {
			fa[edges[x][i]] = x;
			dfs_fa(edges[x][i]);
		}
	}
}

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	mx[x] = max(max(mx[l], mx[r]), val[x]);
	sum[x] = sum[l] + sum[r] + val[x];
}
void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (rev[x]) {
		rev[x] ^= 1; rev[l] ^= 1; rev[r] ^= 1;
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
			if (tr[z][0] == y ^ tr[y][0] == x) rotate(x);
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

void change(int x, int t) {
	access(x);
	splay(x);
	val[x] = t;
	pushup(x);
}
void query_max(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	printf("%d\n", mx[y]);
}
void query_sum(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	printf("%d\n", sum[y]);
}

int main() {
	freopen("1036.in", "r", stdin);
	scanf("%d", &n);
	mx[0] = -INF;
	int x, y;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &x, &y);
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	dfs_fa(1);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
		sum[i] = mx[i] = val[i];
	}
	scanf("%d", &m);
	char op[8];
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		scanf("%d %d", &x, &y);
		if (op[0] == 'C') change(x, y);
		else if (op[1] == 'M') query_max(x, y);
		else query_sum(x, y);
	}

	return 0;
}
