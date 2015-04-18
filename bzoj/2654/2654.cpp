#include <bits/stdc++.h>

using namespace std;

struct Edge{
	int from, to, v, col;
	bool operator < (const Edge &e) const {
		if (v != e.v) return v < e.v;
		return col < e.col;
	}
};

int n, m, need, ans, cnt;
Edge edges[100005];
int fa[100005];

int find(int p) {
	if (p == fa[p]) return p;
	return fa[p] = find(fa[p]);
}

void un(int p, int q) {
	fa[find(p)] = find(q);
}

Edge ee[100005];
int kruskal(int x) {
	cnt = ans = 0;
	for (int i = 0; i <= n; i++)
		fa[i] = i;
	for (int i = 0; i < m; i++) {
		ee[i] = edges[i];
		if (!ee[i].col) {
			ee[i].v += x;
		}
	}
	sort(ee, ee + m);
	for (int i = 0; i < m; i++) {
		int p = ee[i].from;
		int q = ee[i].to;
		if (find(p) != find(q)) {
			un(p, q);
			ans += ee[i].v;
			if (!ee[i].col) cnt++;
		}
	}
}

int main() {
	freopen("2654.in", "r", stdin);
	cin >> n >> m >> need;
	for (int i = 0; i < m; i++) {
		cin >> edges[i].from >> edges[i].to >> edges[i].v >> edges[i].col;
		edges[i].from++;
		edges[i].to++;
	}
	int l = -105, r = 105;
	int res = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		kruskal(mid);
		if (cnt >= need) {
			res = ans - mid * need;
			l = mid + 1;
		}
		else r = mid - 1;
	}

	cout << res << endl;

	return 0;
}
