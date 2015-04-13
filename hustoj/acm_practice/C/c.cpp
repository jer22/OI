#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <utility>

#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)
#define getb(x, y, k) (y - (k * x))
#define getx(k1, b1, k2, b2) ((b1 - b2) / (k2 - k1))
#define gety(k, x, b) (k * x + b)
#define getk(p) (p & 1) ? 1 : -1
#define move(nax, nay, nbx, nby) ax = nax, ay = nay, bx = nbx, by = nby;
#define eps 1e-8

using namespace std;

int T, n, m;
int ax, ay, bx, by;
int pa, pb;

bool check(int da, int db, int px, int py) {
	if (fabs(da - db) > eps) return false;
	if (px < -eps || py < -eps || px > n + eps || py > m + eps) return false;
	if (fabs(ax - bx) < eps && pa + pb != 5) return false;
	if (fabs(ay - by) < eps && pa + pb == 5) return false;
	return true;
}

void change(int x, int y, int &p) {
	if (x == n) p = (p == 1) ? 2 : ((p == 4) ? 3 : p);
	if (y == m) p = (p == 1) ? 4 : ((p == 2) ? 3 : p);
	if (!x) p = (p == 2) ? 1 : ((p == 3) ? 4 : p);
	if (!y) p = (p == 3) ? 2 : ((p == 4) ? 1 : p);
}

int getdist(int x, int y, int pos) {
	switch(pos) {
		case 1 : return min(n - x, m - y);
		case 2 : return min(x, m - y);
		case 3 : return min(x, y);
		case 4 : return min(n - x, y);
	}
}

pii next_pos(int x, int y, int pos, int dist) {
	int dx, dy;
	if (pos == 1) dx = dy = 1;
	else if (pos == 2) dx = -1, dy = 1;
	else if (pos == 3) dx = dy = -1;
	else dx = 1, dy = -1;
	return mp(x + dx * dist, y + dy * dist);
}

bool solve() {
	int cnt = 0;
	while (cnt++ <= 1000000) {
		change(ax, ay, pa), change(bx, by, pb);
		int dist1 = getdist(ax, ay, pa);
		int dist2 = getdist(bx, by, pb);
		int dist = min(dist1, dist2);
		pii na = next_pos(ax, ay, pa, dist);
		pii nb = next_pos(bx, by, pb, dist);
		int ka = getk(pa);
		int kb = getk(pb);
		int ba = getb(ax, ay, ka);
		int bb = getb(bx, by, kb);
		if (ka == kb && ba == bb && pa != pb || (ax == bx && ay == by)) {
			double px = (double(ax) + double(bx)) / 2.0;
			double py = (double(ay) + double(by)) / 2.0;
			printf("%.1lf %.1lf\n", px, py);
			return true;
		} else if (ka != kb) {
			double px = getx(double(ka), double(ba), double(kb), double(bb));
			double py = gety(ka, px, ba);
			double da = abs(px - ax);
			double db = abs(px - bx);
			if (check(da, db, px, py)) {
				printf("%.1lf %.1lf\n", px, py);
				return true;
			}
		}
		move(na.first, na.second, nb.first, nb.second);
	}
	return false;
}

int main() {
	// freopen("c.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d:\n", cas);
		scanf("%d %d", &n, &m);
		scanf("%d %d %d %d", &ax, &ay, &bx, &by);
		pa = pb = 1;
		if (!solve()) printf("Collision will not happen.\n");
	}
	return 0;
}
