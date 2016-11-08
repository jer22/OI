#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 200005;

int n, m;
int rev[MAXN], cover[MAXN];
int tr[MAXN][2], fa[MAXN];
int q[MAXN], top = 0;
int val[MAXN], loop[MAXN];
// vector<int> edges[MAXN];

// void pushup(int x) {
// 	int l = tr[x][0], r = tr[x][1];
// 	// mx[x] = max(max(mx[l], mx[r]), val[x]);
// }
// void pushdown(int x) {
// 	int l = tr[x][0], r = tr[x][1];
// 	if (rev[x]) {
// 		rev[x] ^= 1;
// 		rev[l] ^= 1;
// 		rev[r] ^= 1;
// 		swap(tr[x][0], tr[x][1]);
// 	}
// 	if (cover[x] != -1) {
// 		val[l] = cover[x];
// 		val[r] = cover[x];
// 		cover[x] = -1;
// 	}
// }
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
	// pushup(y);
	// pushup(x);
}
void splay(int x) {
	// top = 0;
	// q[++top] = x;
	// for (int i = x; !isroot(i); i = fa[i])
	// 	q[++top] = fa[i];
	// while (top) pushdown(q[top--]);
	while (!isroot(x)) {
		int y = fa[x], z = fa[y];
		if (!isroot(y)) {
			if (tr[y][0] == x ^ tr[z][0] == y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
int access(int x) {
	int tt = x;
	for (int t = 0; x; t = x, x = fa[x]) {
		splay(x), tr[x][1] = t;
		tt = x;
		// pushup(x);
	}
	return tt;
}
// void makeroot(int x) {
// 	access(x);
// 	splay(x);
// 	rev[x] ^= 1;
// }
// void link(int x, int y) {
// 	makeroot(x);
// 	fa[x] = y;
// }
int find(int x) {
	access(x);
	splay(x);
	while (tr[x][0]) x = tr[x][0];
	return x;
}
void deb() {
	for (int i = 1; i <= n; i++)
		cout << find(i) << " \n"[i == n];
}
void cut(int y, int i = 0) {
	// makeroot(x);
	// access(y);
	cout << i << ' ' << 2 << ' ' << find(2) << endl;
	splay(y);
	if (loop[y]) {
		loop[y] = 0;
		return;
	}
	// pushup(y);
	int t = tr[y][0];
	if (t) while (tr[t][1]) t = tr[t][1];
	else t = fa[y];
	if (!t) return;
	access(t);
	splay(y);
	// access(y);
	// splay(y);
	// if (y) find(y);

	fa[y] = 0;
	if (y == 9) {
		// deb();
	}
}
// void cov(int x, int y, int v) {
// 	makeroot(x);
// 	access(y);
// 	splay(y);
// 	cover[y] = v;
// 	val[y] = v;
// }
int parent[MAXN];
void conn(int x, int y, int i = 0) {
	parent[x] = y;

	if (!y) {
		// makeroot(x);
		loop[x] = y;
		fa[x] = 0;
		return;
	}
	// cout << x << endl;
	if (find(x) == find(y)) {
		// cout << x << ' ' <<  y << ' ' << find(8) << ' ' <<find(9) << endl;
		// cov(x, y, 1);

		loop[x] = y;
		parent[x] = 0;
	} else {
		loop[x] = 0;
		access(x);
		splay(x);
		fa[x] = y;
		if (x == 8 && y == 9) {
			cout << "==========" << i << endl;
			access(5);
			// cout << fa[2] << endl;
			// deb();
		}
		// link(x, y);
	}
}
int query(int x) {
	// access(x);
	// splay(x);
	return val[x];
}

int main() {
	freopen("5967.in", "r", stdin);
	// freopen("ans.out", "w", stdout);
	scanf("%d %d", &n, &m);
	// for (int i = 1; i <= n; i++)
	// 	cover[i] = -1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &parent[i]);
		if (!parent[i]) {
			// makeroot(i);
		} else {
			if (find(parent[i]) != find(i)) {
				fa[i] = parent[i];
				// link(i, parent[i]);
			} else {
				loop[i] = parent[i];
				parent[i] = 0;
			}		
		}
	}

	int op, a, b;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d", &a, &b);
			int t = find(a);
			if (loop[t]) {
				if (t == a) {
					conn(a, b);
				} else {
					// cout << a << ' '<<b <<"===\n";
					cut(a, i);
					conn(t, loop[t], i);
					conn(a, b);

				}
				// loop[t] = 0;
			} else {
				if (t == a) {
					conn(a, b);
				} else {
					cut(a, i);
					conn(a, b);
				}
			}
		} else {
			scanf("%d", &a);
			int rt = find(a);
			// if (a == 9) cout << rt << "ffffff" << endl;
			if (loop[rt]) printf("-1\n");
			else printf("%d\n", rt);
		}
	}

	return 0;
}
