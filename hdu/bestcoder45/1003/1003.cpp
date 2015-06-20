#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 100005;

int n, m;
int rev[MAXN], tag[MAXN];
int tr[MAXN][2], fa[MAXN];
int q[MAXN], top = 0;
int val[MAXN], mx[MAXN];
vector<int> edges[MAXN];

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	mx[x] = mx[l] ^ mx[r] ^ val[x];
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
void add(int x, int y, int v) {
	makeroot(x);
	access(y);
	splay(y);
	val[y] = v;
}
int query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	return mx[y];
}

int T;
int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i <= n; i++) {
			rev[i] = tag[i] = tr[i][0] = tr[i][1] = fa[i] = 0;
			edges[i].clear();
		}
		int a, b;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			link(a, b);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &val[i]);
			val[i]++;
		}
		int op;
		int x, y, z;
		for (int i = 0; i < m; i++) {
			scanf("%d", &op);
			scanf("%d %d", &x, &y);
			if (op == 0) {
				y++;
				add(x, x, y);
			} else {
				int ans = query(x, y);
				if (ans == 0) printf("-1\n");
				else {
					cout << ans - 1 << endl;
				}
			}
		}
	}
	return 0;
}
