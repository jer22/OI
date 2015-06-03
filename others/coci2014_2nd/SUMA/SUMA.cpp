#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#define p(i, j) (((i) - 1) * n + (j))

using namespace std;

const int MAXN = 702;

struct Node{
	int b, oldf, a, olds;
	Node() {}
	Node(int c, int d, int e, int f) : b(c), oldf(d), a(e), olds(f) {}
};

struct Event{
	int a, b, k, l;
	Event() {}
	Event(int c, int d, int e, int f) : a(c), b(d), k(e), l(f) {}
	bool operator < (const Event &e) const {
		return (long long)l * e.k < (long long)k * e.l;
	}
};

int n;
int arr[MAXN][MAXN];
int v[MAXN][MAXN];
int fa[MAXN * MAXN];
int siz[MAXN * MAXN];
int dir[2][2] = {{1, 0}, {0, 1}};

stack<Node> change;
vector<Event> eve;
int find(int p, bool f = 1) {
	if (p == fa[p]) return p;
	int newp = find(fa[p]);
	if (!f) change.push(Node(p, fa[p], -1, -1));
	return fa[p] = newp;
}

int un(int p, int q, bool f = 0) {
	int a = find(p, f);
	int b = find(q, f);
	if (a == b) return siz[a];
	if (siz[a] < siz[b]) swap(a, b);
	if (!f) change.push(Node(b, fa[b], a, siz[a]));
	siz[a] += siz[b];
	fa[b] = a;
	return siz[a];
}

void fuck(int x1, int y1, int x2, int y2) {
	if (x2 > n || y2 > n) return;
	int dk = v[x2][y2] - v[x1][y1];
	int db = arr[x1][y1] - arr[x2][y2];
	if (!dk) {
		if (!db) un(p(x1, y1), p(x2, y2), 1);
		return;
	}
	if (dk < 0) dk = -dk, db = -db;
	if (db < 0) return;
	eve.push_back(Event(p(x1, y1), p(x2, y2), dk, db));
}

void restore() {
	while (!change.empty()) {
		Node c = change.top();
		change.pop();
		fa[c.b] = c.oldf;
		if (c.a != -1)
			siz[c.a] = c.olds;
	}
}

int main() {
	freopen("SUMA.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &arr[i][j]);
			fa[p(i, j)] = p(i, j);
			siz[p(i, j)] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &v[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 0; k < 2; k++)
				fuck(i, j, i + dir[k][0], j + dir[k][1]);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			find(p(i, j));
			ans = max(ans, siz[p(i, j)]);
			// cout << siz[p(i, j)] << endl;
		}
	}
	sort(eve.begin(), eve.end());
	for (int i = 0; i < eve.size(); i++) {
		Event e = eve[i];
		ans = max(ans, un(e.a, e.b));
		if (i == eve.size() - 1 || e < eve[i + 1]) restore();
	}
	cout << ans << endl;
	return 0;
}
