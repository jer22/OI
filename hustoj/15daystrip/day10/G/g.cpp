#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;

struct Point{
	long long x, y;
	Point() {}
	Point(long long a, long long b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};

int T, n;
Point p[MAXN];
bool cmp(int a, int b) { return p[a].y < p[b].y; }

int temp[MAXN];

long long getdist(int a, int b) {
	return (p[a].x - p[b].x) * (p[a].x - p[b].x) + (p[a].y - p[b].y) * (p[a].y - p[b].y);
}

long long dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
int A, B;
long long ret;
void update(int l, int r) {
	if (getdist(l, r) < ret) {
		ret = getdist(l, r);
		A = l;
		B = r;
	}
}
long long solve(int l, int r) {
	int mid = l + r >> 1;
	if (l + 1 == r) {
		update(l, r);
		return getdist(l, r);
	}
    if (l + 2 == r) {
        update(l, r);
        update(l, l + 1);
        update(l + 1, r);
        return min(getdist(l, l + 1), min(getdist(l, r), getdist(l + 1, r)));
    }
	long long best = min(solve(l, mid), solve(mid + 1, r));
	int tot = 0;
	for (int i = l; i <= r; i++) {
		if ((p[i].x - p[mid].x) * (p[i].x - p[mid].x) < best) temp[tot++] = i;
	}
	sort(temp, temp + tot, cmp);
	for (int i = 0; i < tot; i++)
		for (int j = i + 1; j < tot; j++)
			if ((p[temp[j]].y - p[temp[i]].y) * (p[temp[j]].y - p[temp[i]].y) >= best) break;
			else {
				update(temp[i], temp[j]);
				best = min(best, getdist(temp[i], temp[j]));
			}
	return best;
}

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		ret = 10000000000000;
		for (int i = 1; i <= n; i++)
			scanf("%lld %lld", &p[i].x, &p[i].y);
		sort(p + 1, p + n + 1);
		long long ans = solve(1, n);
		Point t = p[A];
		p[A].x = p[A].y = 0x3f3f3f3f;

		long long aa = solve(1, n);


		// if (ans.idx1 > ans.idx2)
		p[A] = t;
		p[B] = Point(0x3f3f3f3f, 0x3f3f3f3f);
		// else p[ans.idx2 - 1] = Point(0x3f3f3f3f, 0x3f3f3f3f);

		// sort(p + 1, p + n + 1);
		long long bb = solve(1, n);

		long long rr = aa + bb + (n - 2) * ans;
		printf("%lld\n", rr);
	}



	return 0;
}
