#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define pll pair<long long, long long>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 200005;

int n, m;
int rev[MAXN << 1];
int tr[MAXN << 1][2], fa[MAXN << 1];
int q[MAXN << 1], top = 0;
long long val[MAXN << 1], mx[MAXN << 1], idx[MAXN << 1];
vector<int> edges[MAXN << 1];

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	idx[x] = x;
	mx[x] = val[x];
	if (mx[l] > val[x]) {
		mx[x] = mx[l];
		idx[x] = idx[l];
	}
	if (mx[r] > mx[x]) {
		mx[x] = mx[r];
		idx[x] = idx[r];
	}
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
pll query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	return mp(mx[y], idx[y]);
}

struct Edge{
	int from, to, id;
	long long val, cost;
	Edge() {}
	bool operator < (const Edge &e) const {
		return val < e.val;
	}
}es[MAXN];
int parent[MAXN];
int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}
void un(int i, int j) {
	parent[find(i)] = find(j);
}

long long money;
bool vis[MAXN];
int main() {
	freopen("f.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> es[i].val;
		es[i].id = i;
		val[i + n] = mx[i + n] = es[i].val;
	}
	for (int i = 1; i <= m; i++)
		cin >> es[i].cost;
	for (int i = 1; i <= m; i++)
		scanf("%d %d", &es[i].from, &es[i].to);
	cin >> money;
	for (int i = 1; i <= n; i++) {
		val[i] = mx[i] = -INF;
		parent[i] = i;
	}
	sort(es + 1, es + m + 1);
	long long tot = 0;
	for (int i = 1; i <= m; i++) {
		int x = es[i].from, y = es[i].to;
		if (find(x) != find(y)) {
			un(x, y);
			tot += es[i].val;
			vis[es[i].id] = 1;
			link(x, es[i].id + n);
			link(y, es[i].id + n);
			// cout << x << ' ' << y << ' ' << es[i].val << endl;
		}
	}
	long long best = tot;
	int red = -1, rem = -1;
	for (int i = 1; i <= m; i++) {
		int x = es[i].from, y = es[i].to;
		pll t = query(x, y);
		long long now = tot - t.first + es[i].val - money / es[i].cost;
		// cout << x << ' ' << y << ' ' << t.first << ' ' << es[i].val << endl;
		if (now < best) {
			best = now;
			red = es[i].id;
			rem = t.second - n;
		}
	}
	cout << best << endl;
	if (red != -1) vis[red] = 1;
	if (rem != -1 && rem != red) vis[rem] = 0;

	for (int i = 1; i <= m; i++) {
		if (!vis[es[i].id]) continue;
		if (es[i].id == red) {
			cout << es[i].id << ' ' << es[i].val - money / es[i].cost << endl;
		} else {
			cout << es[i].id << ' ' << es[i].val << endl;
		}
	}
	return 0;
}
