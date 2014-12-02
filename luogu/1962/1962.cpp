#include <cstdio>
#include <cstring>
#include <algorithm>

#define MOD 1000000007

using namespace std;

struct Martix{
	int n, m;
	long long a[5][5];
	void init(int tn, int tm) {
		n = tn;
		m = tm;
		memset(a, 0, sizeof(a));
	}
}origin;

Martix operator * (Martix a, Martix b) {
	Martix c;
	c.init(a.n, b.m);
	for (int i = 1; i <= a.n; i++) {
		for (int j = 1; j <= b.m; j++) {
			for (int k = 1; k <= a.m; k++) {
				c.a[i][j] += (a.a[i][k] % MOD) * (b.a[k][j] % MOD);
				c.a[i][j] %= MOD;
			}
		}
	}
	return c;
}

Martix operator ^ (Martix a, long long b) {
	Martix c;
	c.init(a.n, a.m);
	for (int i = 1; i <= c.n; i++) {
		c.a[i][i] = 1;
	}
	while (b) {
		if (b & 1) {
			c = c * a;
		}
		b >>= 1;
		a = a * a;
	}
	return c;
}

long long n;
int main() {
	freopen("1962.in", "r", stdin);
	scanf("%lld", &n);
	if (n == 1) printf("1\n");
	else if (!n) printf("0\n");
	else {
		origin.init(1, 2);
		origin.a[1][1] = origin.a[1][2] = 1;
		Martix base;
		base.init(2, 2);
		base.a[1][2] = base.a[2][1] = base.a[2][2] = 1;
		base = base ^ (n - 2);
		origin = origin * base;
		printf("%lld\n", origin.a[1][2]);
	}
	return 0;
}
