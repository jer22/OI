#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define lch rt << 1
#define rch rt << 1 | 1
#define mid (l + r >> 1)
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int n, m, S;
vector<Edge> edges[MAXN << 4];
int id[MAXN], idup[MAXN << 2], iddo[MAXN << 2], tot = 0;

void build(int l, int r, int rt) {
	idup[rt] = ++tot;
	iddo[rt] = ++tot;
	if (l == r) {
		id[l] = ++tot;
		edges[id[l]].push_back(Edge(idup[rt], 0));
		edges[iddo[rt]].push_back(Edge(id[l], 0));
		return;
	}
	build(lson);
	build(rson);
	edges[idup[lch]].push_back(Edge(idup[rt], 0));
	edges[idup[rch]].push_back(Edge(idup[rt], 0));
	edges[iddo[rt]].push_back(Edge(iddo[lch], 0));
	edges[iddo[rt]].push_back(Edge(iddo[rch], 0));
}

void update1(int l, int r, int rt, int x, int L, int R, long long v) {
	if (L <= l && r <= R) {
		edges[id[x]].push_back(Edge(iddo[rt], v));
		return;
	}
	if (L <= mid) update1(lson, x, L, R, v);
	if (R > mid) update1(rson, x, L, R, v);
}

void update2(int l, int r, int rt, int x, int L, int R, long long v) {
	if (L <= l && r <= R) {
		edges[idup[rt]].push_back(Edge(id[x], v));
		return;
	}
	if (L <= mid) update2(lson, x, L, R, v);
	if (R > mid) update2(rson, x, L, R, v);
}

long long dist[MAXN << 4];
bool vis[MAXN << 4];
const long long INF = 100000000000000000ll;
void spfa() {
	queue<int> q;
	for (int i = 0; i <= tot; i++) {
		dist[i] = INF;
		vis[i] = 0;
	}
	q.push(id[S]);
	dist[id[S]] = 0;
	vis[id[S]] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (auto e : edges[cur]) {
			if (dist[cur] + e.v < dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
				if (!vis[e.to]) {
					q.push(e.to);
					vis[e.to] = 1;
				}
			}
		}
	}

}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &S);
	build(1, n, 1);
	for (int i = 1; i <= n; i++) {
		
	}
	int op, a, b, c;
	long long d;
	for (int i = 0; i < m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d %lld", &a, &b, &d);
			edges[id[a]].push_back(Edge(id[b], d));
		} else if (op == 2) {
			scanf("%d %d %d %lld", &a, &b, &c, &d);
			update1(1, n, 1, a, b, c, d);
		} else {
			scanf("%d %d %d %lld", &a, &b, &c, &d);
			update2(1, n, 1, a, b, c, d);
		}
	}
	spfa();
	for (int i = 1; i <= n; i++)
		cout << ((dist[id[i]] != INF) ? dist[id[i]] : -1) << endl;

	return 0;
}
