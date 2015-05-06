#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 3;
const long long MOD = 1000000007LL;

struct martrix {
	int n, m;
	long long a[MAXN][MAXN];
	inline void init(const int &tn, const int &tm) {
		n = tn;
		m = tm;
		memset(a, 0, sizeof(a));
	}
}origin;

inline martrix operator *(const martrix a, const martrix b) {
	if (a.m != b.n) {
		printf("error");
	}
	martrix c;
	c.init(a.n, b.m);
	int i, j, k;
	for (i = 0; i < a.n; i++) {
		for (j = 0; j < b.m; j++) {
			for (k = 0; k < a.m; k++) {
				c.a[i][j] = (c.a[i][j] + (a.a[i][k] * b.a[k][j]) % MOD) % MOD;
			}
		}
	}
	return c;
}

inline martrix pow(martrix a, int x) {
	martrix res;
	res.init(a.n, a.m);
	for (int i = 0; i < a.n; i++) {
		res.a[i][i] = 1;
	}
	while (x) {
		if (x & 1) {
			res = res * a;
		}
		x >>= 1;
		a = a * a;
	}
	return res;
}

int n;
int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%d", &n)) {
		origin.init(1, 2);
		origin.a[0][0] = 0;
		origin.a[0][1] = 1;
		martrix base;
		base.init(2, 2);
		base.a[0][1] = base.a[1][0] = 1;
		base.a[1][1] = 2;
		if (n == 0) printf("0\n");
		else if (n == 1) printf("1\n");
		else {
			n--;
			martrix ans = pow(base, n);
			ans = origin * ans;
			printf("%lld\n", ans.a[0][1]);
		}
	}


	return 0;
}
