#include <bits/stdc++.h>

const int MAXN = 200005;

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		return x < p.x;
	}
}p[MAXN];

bool cmpy(const Point &a, const Point &b) {
	return a.y < b.y;
}

int n;
long long c[MAXN];
int lowbit(int x) { return x & (-x); }
void insert(int p, int v) {
	for (int i = p; i < MAXN; i += lowbit(i))
		c[i] += (long long)v;
}
long long getans(int p) {
	if (p <= 0) return 0;
	long long ans = 0;
	for (int i = p; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

long long ans = 0;
Point tmp[MAXN];
Point s1[MAXN], s2[MAXN];
int t1 = 0, t2 = 0;
void solve(int l, int r) {
	if (l >= r) return;
	int mid = l + r >> 1;
	for (int i = l; i <= r; i++)
		tmp[i] = p[i];
	sort(tmp + l, tmp + mid + 1, cmpy);
	sort(tmp + mid + 1, tmp + r + 1, cmpy);
	int j = l;
	// if (l == 3) cout << tmp[mid + 1].y << endl;
	for (int i = mid + 1; i <= r; i++) {

		while (t1 && tmp[i].x < s1[t1].x) t1--;
		s1[++t1] = tmp[i];
		for (; tmp[j].y < tmp[i].y && j <= mid; j++) {
			while (t2 && tmp[j].x > s2[t2].x) {
				insert(s2[t2].y, -1);
				t2--;
			}
			s2[++t2] = tmp[j];
			insert(s2[t2].y, 1);
		}
		ans += getans(tmp[i].y) - getans(s1[t1 - 1].y - 1);
	}
	t1 = 0;
	while (t2) {
		insert(s2[t2].y, -1);
		t2--;
	}
	solve(l, mid);
	solve(mid + 1, r);
}

int main() {
	freopen("4237.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].x, &p[i].y);
	sort(p + 1, p + n + 1, cmpy);
	for (int i = 1; i <= n; i++)
		p[i].y = i;
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++)
		p[i].x = i;
	s1[0] = Point(0, 0);
	solve(1, n);
	printf("%lld\n", ans);
	return 0;
}
