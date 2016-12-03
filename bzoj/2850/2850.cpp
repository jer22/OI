#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;

int nowD;
struct Point{
	long long x, y, v;
	Point(long long _x = 0, long long _y = 0, long long _v = 0) : x(_x), y(_y), v(_v) {}
	friend bool operator < (Point a, Point b) {
		if (nowD) return a.x < b.x;
		return a.y < b.y;
	}
}P[MAXN];

struct Node{
	Point p;
	int x[2], y[2];
	long long sum;
	Node *l, *r;
	void set(Point _) {
		p = _;
		x[0] = x[1] = _.x;
		y[0] = y[1] = _.y;
		sum = _.v;
	}
	void update(Node *s) {
		x[0] = min(x[0], s -> x[0]);
		x[1] = max(x[1], s -> x[1]);
		y[0] = min(y[0], s -> y[0]);
		y[1] = max(y[1], s -> y[1]);
		sum += s -> sum;
	}
}tr[MAXN], *top = tr, Tnull, *null = &Tnull;

Node *build(int l, int r, int d) {
	if (l > r) return null;
	nowD = d;
	int mid = l + r >> 1;
	Node *newnode = top++;
	nth_element(P + l + 1, P + mid + 1, P + r + 1);
	newnode -> set(P[mid]);
	newnode -> l = build(l, mid - 1, d ^ 1);
	newnode -> r = build(mid + 1, r, d ^ 1);
	if (newnode -> l != null) newnode -> update(newnode -> l);
	if (newnode -> r != null) newnode -> update(newnode -> r);
	return newnode;
}
long long a, b, c;
bool check(Point p) {
	return p.x * a + p.y * b < c;
}
int calc(Node *rt) {
	if (rt == null) return 0;
	return check(Point(rt -> x[0], rt -> y[0]))
		+ check(Point(rt -> x[0], rt -> y[1]))
		+ check(Point(rt -> x[1], rt -> y[0]))
		+ check(Point(rt -> x[1], rt -> y[1]));
}

long long ans;
long long query(Node *rt) {
	if (check(rt -> p)) ans += rt -> p.v;
	long long sl = calc(rt -> l);
	long long sr = calc(rt -> r);
	if (sl == 4) ans += rt -> l -> sum;
	else if (sl) query(rt -> l);
	if (sr == 4) ans += rt -> r -> sum;
	else if (sr) query(rt -> r);
}

int n, m;
int main() {
	freopen("2850.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld %lld %lld", &P[i].x, &P[i].y, &P[i].v);
	Node *root = build(1, n, 0);
	while (m--) {
		scanf("%lld %lld %lld", &a, &b, &c);
		ans = 0;
		query(root);
		printf("%lld\n", ans);
	}

	return 0;
}
