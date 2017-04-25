#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

struct Hor{
	int pos, spd;
	Hor() {}
	Hor(int a, int b) : pos(a), spd(b) {}
	bool operator < (const Hor &h) const {
		return pos < h.pos;
	}
};

int T;
int n;
double d;
Hor horses[MAXN];
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%lf %d", &d, &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &horses[i].pos, &horses[i].spd);
		}
		sort(horses + 1, horses + n + 1);
		double lstt = 0;
		for (int i = n; i >= 1; i--) {
			double tim = double(d - horses[i].pos) / horses[i].spd;
			lstt = max(lstt, tim);
		}
		double ans = d / lstt;
		printf("Case #%d: %.10lf\n", cas, ans);
	}


	return 0;
}
