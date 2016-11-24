#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 200005;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int n, m;
int rev[MAXN];
long long tag[MAXN];
int tr[MAXN][2], fa[MAXN];
int q[MAXN], top = 0;
long long val[MAXN], mx[MAXN];
vector<Edge> edges[MAXN];
long long arr[MAXN];

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
void add(int x, int y, long long v) {
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
}

#define pli pair<long long, int>
#define mp(i, j) make_pair((i), (j))
int tot = 0;
pli roa[MAXN];
void dfs(int x) {
	if (x != 1) {
		int l = 0, r = tot - 1;
		while (l < r) {
			int mid = (l + r >> 1);
			if (arr[x] + roa[tot].first >= roa[mid].first) r = mid;
			else l = mid + 1;
		}
		// if (x == 5) {
		// 	for (int i = 0; i <= tot; i++) {
		// 		cout << roa[i].first << endl;
		// 	}
		// }
		if (arr[x] + roa[tot].first < roa[r].first) r++;
		// cout << r << endl;
		if (r < tot) {
			// cout << roa[r + 1].second << endl;
			add(roa[r + 1].second, roa[tot].second, 1);
		}
	}
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		roa[++tot] = mp(-e.v + roa[tot - 1].first, x);
		dfs(e.to);
		tot--;
	}
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	int a;
	long long b;
	for (int i = 2; i <= n; i++) {
		scanf("%d %lld", &a, &b);
		link(i, a);
		edges[a].push_back(Edge(i, b));
	}
	roa[0] = mp(0, 1);
	dfs(1);
	for (int i = 1; i <= n; i++) {
		query(i, i);
		if (i > 1) printf(" ");
		printf("%lld", mx[i]);
	}
	printf("\n");
	return 0;
}
