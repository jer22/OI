#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const long long INF = 1000000000000000000;

int nowD;
struct Point{
	int id;
	long long x, y, v;
	Point(long long a = 0, long long b = 0, long long c = 0, int d = 0) : x(a), y(b), v(c), id(d) {}
	bool operator < (const Point &p) const {
		if (nowD) return x < p.x;
		return y < p.y;
	}
}P[MAXN];
long long dis(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct Node{
	Node *l, *r;
	Point p;
	long long x[2], y[2];
	long long mi;
	void set(Point _) {
		p = _;
		x[0] = x[1] = _.x;
		y[0] = y[1] = _.y;
		mi = p.v;
	}
	long long dis(Point _) {
		long long res = 0;
		if (_.x < x[0] || _.x > x[1])
			res += min((_.x - x[0]) * (_.x - x[0]), (_.x - x[1]) * (_.x - x[1]));
		if (_.y < y[0] || _.y > y[1])
			res += min((_.y - y[0]) * (_.y - y[0]), (_.y - y[1]) * (_.y - y[1]));
		return res;
	}
	void update(Node *s) {
		x[0] = min(x[0], s -> x[0]);
		x[1] = max(x[1], s -> x[1]);
		y[0] = min(y[0], s -> y[0]);
		y[1] = max(y[1], s -> y[1]);
		mi = min(mi, s -> mi);
	}
}tr[MAXN], *top = tr, Tnull, *null = &Tnull;

Point ansp;
long long ans;
void getmin(Node *rt, Point p) {
	if (rt -> p.v <= p.v) {
		long long t = dis(rt -> p, p);
		if (t < ans || ((t == ans) && (rt -> p.id < ansp.id))) {
			ans = t;
			ansp = rt -> p;
		}
	}
	long long disl = (rt -> l != null && rt -> l -> mi <= p.v) ? rt -> l -> dis(p) : INF;
	long long disr = (rt -> r != null && rt -> r -> mi <= p.v) ? rt -> r -> dis(p) : INF;
	if (disl < disr) {
		if (rt -> l != null && rt -> l -> mi <= p.v) getmin(rt -> l, p);
		if (disr < ans && rt -> r != null) getmin(rt -> r, p); 
	} else {
		if (rt -> r != null && rt -> r -> mi <= p.v) getmin(rt -> r, p);
		if (disl < ans && rt -> l != null) getmin(rt -> l, p);
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

Node *build(int l, int r, int d) {
	if (l > r) return null;
	int mid = l + r >> 1;
	nowD = d;
	nth_element(P + l + 1, P + mid + 1, P + r + 1);
	Node *newnode = top++;
	newnode -> set(P[mid]);
	newnode -> l = build(l, mid - 1, d ^ 1);
	newnode -> r = build(mid + 1, r, d ^ 1);
	if (newnode -> l != null) newnode -> update(newnode -> l);
	if (newnode -> r != null) newnode -> update(newnode -> r);
	return newnode;
}

int cmpv(Point a, Point b) {
	return a.v < b.v;
}
int T;
int n, m;
int main() {
	freopen("5992.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%lld %lld %lld", &P[i].x, &P[i].y, &P[i].v);
			P[i].id = i;
		}
		Node *root = build(1, n, 0);
		long long a, b, c;
		for (int i = 1; i <= m; i++) {
			scanf("%lld %lld %lld", &a, &b, &c);
			ans = INF;
			ansp = Point(0, 0, 0, 0x3f3f3f3f);
			getmin(root, Point(a, b, c));
			printf("%lld %lld %lld\n", ansp.x, ansp.y, ansp.v);
		}
	}

	return 0;
}
