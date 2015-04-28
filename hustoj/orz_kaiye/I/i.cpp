#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAXN 15
#define MOD 10000007

using namespace std;

int n, m;

struct martrix {
	int n, m;
	long long a[MAXN][MAXN];
	inline void init(const int &tn, const int &tm) {
		n = tn;
		m = tm;
		memset(a, 0, sizeof(a));
	}
	inline void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << a[i][j] << ' ';
			}
			cout << endl;
		}
	}
}origin;

inline martrix operator *(const martrix &a, const martrix &b) {
	if (a.m != b.n) {
		printf("error");
	}
	martrix c;
	c.init(a.n, b.m);
	int i, j, k;
	for (i = 0; i < a.n; i++) {
		for (j = 0; j < b.m; j++) {
			for (k = 0; k < a.m; k++) {
				long long t = a.a[i][k] * b.a[k][j] % MOD;
				c.a[i][j] += t;
				c.a[i][j] %= MOD;
			}
		}
	}
	return c;
}

inline martrix pow(const martrix &a, int x) {
	martrix res;
	res.init(a.n, a.m);
	for (int i = 0; i < a.n; i++) {
		res.a[i][i] = 1;
	}
	while (x) {
		if (x & 1) {
			res = res * origin;
		}
		x >>= 1;
		origin = origin * origin;
	}
	return res;
}

martrix base;
int main( void ) {
	freopen("i.in", "r", stdin);
	while (~scanf("%d %d", &n, &m))  {
		int t;
		origin.init(n + 2, n + 2);
		for (int i = 0; i < n + 2; i++)
			origin.a[0][i] = 1;
		for (int i = 1; i < n + 2; i++)
			origin.a[1][i] = 10;
		for (int i = 2; i < n + 2; i++)
			for (int j = i; j < n + 2; j++)
				origin.a[i][j] = 1;
		// origin.print();
		base.init(1, n + 2);
		base.a[0][0] = 3;
		base.a[0][1] = 233;
		for (int i = 0; i < n; i++) {
			scanf("%d", &t);
			base.a[0][i + 2] = base.a[0][i + 1] + t;
		}
		origin = pow(origin, m - 1);
		origin = base * origin;
		cout << origin.a[0][n + 1] << endl;
	}

	
	return 0;
}
