#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;
const int MAXM = 500005;
const int INF = 0x3f3f3f3f;

struct Point{
	int x, y;
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
}P[MAXN + MAXM];
int dis(const Point &a, const Point &b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}
bool nowD;
bool operator < (Point a, Point b) {
	if (nowD) return a.x < b.x;
	return a.y < b.y;
}

struct Node{
	Node *l, *r;
	int x[2], y[2];
	Point p;
	void set(Point _) {
		p = _;
		x[0] = x[1] = _.x;
		y[0] = y[1] = _.y;
	}
	int dis(Point _) {
		int res = 0;
		if (_.x < x[0] || _.x > x[1])
			res += (_.x < x[0]) ? x[0] - _.x : _.x - x[1];
		if (_.y < y[0] || _.y > y[1])
			res += (_.y < y[0]) ? y[0] - _.y : _.y - y[1];
		return res;
	}
	void update(Node *s) {
		x[0] = min(x[0], s -> x[0]);
		x[1] = max(x[1], s -> x[1]);
		y[0] = min(y[0], s -> y[0]);
		y[1] = max(y[1], s -> y[1]);
	}
}tr[MAXN + MAXM], *top = tr, Tnull, *null = &Tnull;

Node *build(int l, int r, bool d) {
	if (l > r) return null;
	int mid = l + r >> 1;
	nowD = d;
	nth_element(P + l + 1, P + mid + 1, P + r + 1);
	Node *q = top++;
	q -> set(P[mid]);
	q -> l = build(l, mid - 1, d ^ 1);
	q -> r = build(mid + 1, r, d ^ 1);
	if (q -> l != null) q -> update(q -> l);
	if (q -> r != null) q -> update(q -> r);
	return q;
}
int mi;
void getmin(Node *rt, Point p) {
	mi = min(mi, dis(rt -> p, p));
	int disl = rt -> l != null ? rt -> l -> dis(p) : INF;
	int disr = rt -> r != null ? rt -> r -> dis(p) : INF;
	if (disl < disr) {
		if (rt -> l != null) getmin(rt -> l, p);
		if (disr < mi && rt -> r != null) getmin(rt -> r, p); 
	} else {
		if (rt -> r != null) getmin(rt -> r, p);
		if (disl < mi && rt -> l != null) getmin(rt -> l, p);
	}
}
void insert(Node *rt, Point p) {
	Node *newnode = top++;
	newnode -> l = newnode -> r = null;
	newnode -> set(p);
	nowD = 0;
	while (1) {
		rt -> update(newnode);
		if (newnode -> p < rt -> p) {
			if (rt -> l == null) {
				rt -> l = newnode;
				break;
			} else rt = rt -> l;
		} else {
			if (rt -> r == null) {
				rt -> r = newnode;
				break;
			} else rt = rt -> r;
		}
		nowD ^= 1;
	}
}

int n, m;
int main() {
	freopen("2648.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &P[i].x, &P[i].y);
	Node *root = build(1, n, 0);
	int a, b, op;
	while (m--) {
		scanf("%d %d %d", &op, &a, &b);
		if (op == 1) insert(root, Point(a, b));
		else {
			mi = INF;
			getmin(root, Point(a, b));
			printf("%d\n", mi);
		}
	}

	return 0;
}
