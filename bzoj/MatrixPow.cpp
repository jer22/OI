#include <iostream>
#include <cstdio>
#include <cstring>

#define MAXN 30

using namespace std;

int n, p;

struct matrix {
	int n, m;
	int a[MAXN][MAXN];
	inline void init(const int &tn, const int &tm) {
		n = tn;
		m = tm;
		memset(a, 0, sizeof(a));
	}
}origin;

inline matrix operator *(const matrix &a, const matrix &b) {
	if (a.m != b.n) {
		printf("error");
	}
	matrix c;
	c.init(a.n, b.m);
	int i, j, k;
	for (i = 0; i < a.n; i++) {
		for (j = 0; j < b.m; j++) {
			for (k = 0; k < a.m; k++) {
				c.a[i][j] += a.a[i][k] * b.a[k][j];
			}
		}
	}
	return c;
}

inline matrix pow(const matrix &a, int x) {
	matrix res;
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

int main( void ) {
	cin >> n;
	origin.init(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &origin.a[i][j]);
		}
	}
	cin >> p;
	matrix r = pow(origin, p);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", r.a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
