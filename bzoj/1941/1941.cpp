#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;
const int INF = 0x7f7f7f7f;

struct Point{
	int x, y, id;
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
}P[MAXN];
int dis(Point a, Point b) {
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
	int mindis(Point _) {
		int res = 0;
		if (_.x < x[0] || _.x > x[1])
			res += (_.x < x[0]) ? x[0] - _.x : _.x - x[1];
		if (_.y < y[0] || _.y > y[1])
			res += (_.y < y[0]) ? y[0] - _.y : _.y - y[1];
		return res;
	}
	int maxdis(Point _) {
		return max(abs(x[0] - _.x), abs(x[1] - _.x))
			+ max(abs(y[0] - _.y), abs(y[1] - _.y));
	}
	void update(Node *s) {
		x[0] = min(x[0], s -> x[0]);
		x[1] = max(x[1], s -> x[1]);
		y[0] = min(y[0], s -> y[0]);
		y[1] = max(y[1], s -> y[1]);
	}
}tr[MAXN], *top = tr, Tnull, *null = &Tnull;

Node * build(int l, int r, bool d) {
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
int mi, mx;
void getmin(Node *rt, Point p) {
	if (dis(rt -> p, p)) mi = min(mi, dis(rt -> p, p));
	int disl = rt -> l != null ? rt -> l -> mindis(p) : INF;
	int disr = rt -> r != null ? rt -> r -> mindis(p) : INF;
	if (disl < disr) {
		if (disl < mi) getmin(rt -> l, p);
		if (disr < mi) getmin(rt -> r, p);
	} else {
		if (disr < mi) getmin(rt -> r, p);
		if (disl < mi) getmin(rt -> l, p);
	}
}
void getmax(Node *rt, Point p) {
	mx = max(mx, dis(rt -> p, p));
	int disl = rt -> l != null ? rt -> l -> maxdis(p) : -INF;
	int disr = rt -> r != null ? rt -> r -> maxdis(p) : -INF;
	if (disl > disr) {
		if (disl > mx) getmax(rt -> l, p);
		if (disr > mx) getmax(rt -> r, p);
	} else {
		if (disr > mx) getmax(rt -> r, p);
		if (disl > mx) getmax(rt -> l, p);
	}
}

int n;
int main() {
	freopen("1941.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &P[i].x, &P[i].y);
		P[i].id = i;
	}
	Node *root = build(1, n, 0);
	int ans = INF;
	for (int i = 1; i <= n; i++) {
		mi = INF, mx = -INF;
		getmin(root, P[i]);
		getmax(root, P[i]);
		ans = min(ans, mx - mi);
	}
	printf("%d\n", ans);

	return 0;
}
