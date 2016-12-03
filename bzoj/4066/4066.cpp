#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 200005;
bool nowD;
struct Point{
	int x, y, v, idx;
	Point(int a = 0, int b = 0, int c = 0, int d = 0) : x(a), y(b), v(c), idx(d) {}
	bool operator < (const Point &p) const {
		if (nowD) return x < p.x;
		return y < p.y;
	}
	bool operator == (const Point &p) const {
		return x == p.x && y == p.y;
	}
}P[MAXN];

struct Node{
	Node *l, *r;
	Point p;
	int sum, x[2], y[2];
	void set(Point _) {
		p = _;
		sum = _.v;
		x[0] = x[1] = _.x;
		y[0] = y[1] = _.y;
	}
	void update(Node *s) {
		x[0] = min(x[0], s -> x[0]);
		x[1] = max(x[1], s -> x[1]);
		y[0] = min(y[0], s -> y[0]);
		y[1] = max(y[1], s -> y[1]);
		sum += s -> sum;
	}
}tr[MAXN], *top = tr, Tnull, *null = &Tnull;

int m = 1;
void insert(Node *rt, Point p) {
	Node *newnode = top++;
	newnode -> l = newnode -> r = null;
	newnode -> set(p);
	nowD = 0;
	P[p.idx] = p;
	while (1) {
		rt -> update(newnode);
		// if (rt -> p == p) {
		// 	rt -> p.v += p.v;
		// 	P[rt -> p.idx].v += p.v;
		// 	m--;
		// 	break;
		// }
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

int ans;
int x1, yy, x2, y2;
bool check(Point p) {
	return p.x >= x1 && p.x <= x2 && p.y >= yy && p.y <= y2;
}
bool fuck(Node *rt) {
	int a = rt -> x[0], b = rt -> y[0];
	int c = rt -> x[1], d = rt -> y[1];
	return a > x2 || c < x1 || b > y2 || d < yy;
}
int calc(Node *rt) {
	if (rt == null)
		return -1;
	return check(Point(rt -> x[0], rt -> y[0]))
		+ check(Point(rt -> x[0], rt -> y[1]))
		+ check(Point(rt -> x[1], rt -> y[0]))
		+ check(Point(rt -> x[1], rt -> y[1]));
}
void query(Node *rt) {
	if (check(rt -> p)) ans += rt -> p.v;
	int sl = calc(rt -> l);
	int sr = calc(rt -> r);
	if (sl == 4) ans += rt -> l -> sum;
	else if (~sl && !fuck(rt -> l)) query(rt -> l);
	if (sr == 4) ans += rt -> r -> sum;
	else if (~sr && !fuck(rt -> r)) query(rt -> r);
}
Node *rebuild(int l, int r, int d) {
	if (l > r) return null;
	int mid = l + r >> 1;
	nowD = d;
	Node *newnode = top++;
	nth_element(P + l + 1, P + mid + 1, P + r + 1);
	newnode -> set(P[mid]);
	newnode -> l = rebuild(l, mid - 1, d ^ 1);
	newnode -> r = rebuild(mid + 1, r, d ^ 1);
	if (newnode -> l != null) newnode -> update(newnode -> l);
	if (newnode -> r != null) newnode -> update(newnode -> r);
	return newnode;
}

int n;
int main() {
	freopen("4066.in", "r", stdin);
	freopen("4066.out", "w", stdout);
	scanf("%d", &n);
	int op, a, b, c;
	P[1] = Point(0, 0, 0, 1);
	Node *root = rebuild(1, 1, 0);
	int lastans = 0;
	int M = 10000;
	while (~scanf("%d", &op)) {
		if (op == 3) break;
		if (op == 1) {
			scanf("%d %d %d", &a, &b, &c);
			a ^= lastans, b ^= lastans, c ^= lastans;
			insert(root, Point(a, b, c, ++m));
			if (m > M) {
				top = tr;
				root = rebuild(1, m, 0);
				M += 10000;
			}
		} else {
			scanf("%d %d %d %d", &x1, &yy, &x2, &y2);
			ans = 0;
			x1 ^= lastans, yy ^= lastans, x2 ^= lastans, y2 ^= lastans;
			// cout << x1 << ' ' << yy << ' ' << x2 << ' ' << y2 << endl;
			query(root);
			printf("%d\n", ans);
			// lastans = ans;
		}
	}

	return 0;
}
