#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20005;
const long long INF = INT_MAX - 2;

struct Point{
	long long x, y;
	Point() {}
	Point(long long a, long long b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};


vector<Point> cur;

bool fuck(long long d) {
	int siz = cur.size();
	if (siz == 0) return true;
	Point up = {INF, -INF}, lef = {INF, INF}, don = {-INF, INF}, rig = {-INF, -INF};

	for (int i = 0; i < siz; i++) {
		if (cur[i].y > up.y) up = cur[i];
		else if (cur[i].y == up.y && cur[i].x < up.x) up = cur[i];

		if (cur[i].x < lef.x) lef = cur[i];
		else if (cur[i].x == lef.x && cur[i].y < lef.y) lef = cur[i];

		if (cur[i].y < don.y) don = cur[i];
		else if (cur[i].y == don.y && cur[i].x > don.x) don = cur[i];

		if (cur[i].x > rig.x) rig = cur[i];
		else if (cur[i].x == rig.x && cur[i].y > rig.y) rig = cur[i];
	}
	long long ll = min(up.x, lef.x), uu = max(up.y, lef.y);
	long long rr = ll + d, dd = uu - d;
	long long x1 = INF, yy = INF, x2 = -INF, y2 = -INF;
	int cc = 0;
	for (int i = 0; i < siz; i++) {
		if (cur[i].x >= ll && cur[i].x <= rr && cur[i].y <= uu && cur[i].y >= dd) continue;
		cc = 1;
		x1 = min(x1, cur[i].x);
		x2 = max(x2, cur[i].x);
		yy = min(yy, cur[i].y);
		y2 = max(y2, cur[i].y);
	}
	if (!cc) return true;
	else if (x2 - x1 <= d && y2 - yy <= d) {
		return true;
	}

	uu = max(up.y, rig.y), rr = max(up.x, rig.x);
	dd = uu - d, ll = rr - d;
	x1 = INF, yy = INF, x2 = -INF, y2 = -INF;
	cc = 0;
	for (int i = 0; i < siz; i++) {
		if (cur[i].x >= ll && cur[i].x <= rr && cur[i].y <= uu && cur[i].y >= dd) continue;
		cc = 1;
		x1 = min(x1, cur[i].x);
		x2 = max(x2, cur[i].x);
		yy = min(yy, cur[i].y);
		y2 = max(y2, cur[i].y);
	}
	if (!cc) return true;
	else if (x2 - x1 <= d && y2 - yy <= d) {
		return true;
	}

	ll = min(lef.x, don.x), dd = min(lef.y, don.y);
	rr = ll + d, uu = dd + d;
	x1 = INF, yy = INF, x2 = -INF, y2 = -INF;
	cc = 0;
	for (int i = 0; i < siz; i++) {
		if (cur[i].x >= ll && cur[i].x <= rr && cur[i].y <= uu && cur[i].y >= dd) continue;
		cc = 1;
		x1 = min(x1, cur[i].x);
		x2 = max(x2, cur[i].x);
		yy = min(yy, cur[i].y);
		y2 = max(y2, cur[i].y);
	}
	if (!cc) return true;
	else if (x2 - x1 <= d && y2 - yy <= d) {
		return true;
	}

	rr = max(rig.x, don.x), dd = min(rig.y, don.y);
	ll = rr - d, uu = dd + d;
	x1 = INF, yy = INF, x2 = -INF, y2 = -INF;
	cc = 0;
	for (int i = 0; i < siz; i++) {
		if (cur[i].x >= ll && cur[i].x <= rr && cur[i].y <= uu && cur[i].y >= dd) continue;
		cc = 1;
		x1 = min(x1, cur[i].x);
		x2 = max(x2, cur[i].x);
		yy = min(yy, cur[i].y);
		y2 = max(y2, cur[i].y);
	}
	if (!cc) return true;
	else if (x2 - x1 <= d && y2 - yy <= d) {
		return true;
	}
	return false;
}
int n;
Point arr[MAXN];
Point up = {INF, -INF}, lef = {INF, INF}, don = {-INF, INF}, rig = {-INF, -INF};

bool check(int d) {
	long long ll = min(up.x, lef.x), uu = max(up.y, lef.y);
	long long rr = ll + d, dd = uu - d;
	cur.clear();
	for (int i = 1; i <= n; i++) {
		if (arr[i].x >= ll && arr[i].x <= rr && arr[i].y <= uu && arr[i].y >= dd) continue;
		cur.push_back(arr[i]);
	}
	if (fuck(d)) {
		return true;
	}

	uu = max(up.y, rig.y), rr = max(up.x, rig.x);
	dd = uu - d, ll = rr - d;
	cur.clear();
	for (int i = 1; i <= n; i++) {
		if (arr[i].x >= ll && arr[i].x <= rr && arr[i].y <= uu && arr[i].y >= dd) continue;
		cur.push_back(arr[i]);
	}
	if (fuck(d)) return true;

	ll = min(lef.x, don.x), dd = min(lef.y, don.y);
	rr = ll + d, uu = dd + d;
	cur.clear();
	for (int i = 1; i <= n; i++) {
		if (arr[i].x >= ll && arr[i].x <= rr && arr[i].y <= uu && arr[i].y >= dd) continue;
		cur.push_back(arr[i]);
	}
	if (fuck(d)) return true;

	rr = max(rig.x, don.x), dd = min(rig.y, don.y);
	ll = rr - d, uu = dd + d;
	cur.clear();
	for (int i = 1; i <= n; i++) {
		if (arr[i].x >= ll && arr[i].x <= rr && arr[i].y <= uu && arr[i].y >= dd) continue;
		cur.push_back(arr[i]);
	}
	if (fuck(d)) return true;

	return false;
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &arr[i].x, &arr[i].y);
	}
	for (int i = 1; i <= n; i++) {
		if (arr[i].y > up.y) up = arr[i];
		else if (arr[i].y == up.y && arr[i].x < up.x) up = arr[i];

		if (arr[i].x < lef.x) lef = arr[i];
		else if (arr[i].x == lef.x && arr[i].y < lef.y) lef = arr[i];

		if (arr[i].y < don.y) don = arr[i];
		else if (arr[i].y == don.y && arr[i].x > don.x) don = arr[i];

		if (arr[i].x > rig.x) rig = arr[i];
		else if (arr[i].x == rig.x && arr[i].y > rig.y) rig = arr[i];
	}
	long long l = 1, r = INT_MAX - 2;
	while (l < r) {
		long long mid = (long long)l + r >> 1ll;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;

	return 0;
}
