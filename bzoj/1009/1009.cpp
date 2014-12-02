#include <iostream>
#include <cstdio>
#include <cstring>

#define MAXN 30

using namespace std;

int n, m;
int mod;

struct matrix {
	int n, m;
	int a[MAXN][MAXN];
	inline void init(const int &tn, const int &tm) {
		n = tn;
		m = tm;
		memset(a, 0, sizeof(a));
	}
}origin, ans;

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
				c.a[i][j] %= mod;
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

int s[MAXN];
int pre[MAXN];

void kmp() {
	for ( int i = 1 , j = 0 ; i ++ < m ; ) {
		for ( ; j && s[ i ] != s[ j + 1 ] ; j = pre[ j ] ) ;
		if ( s[ j + 1 ] == s[ i ] ) ++ j ;
		pre[ i ] = j ;
	}
}

int main( void ) {
	cin >> n >> m >> mod;
	char ch;
	for (int i = 0; i++ < m; ) {
		for (ch = getchar(); !(ch >= '0' && ch <= '9'); ch = getchar());
		s[i] = ch - '0';
	}

	kmp();

	origin.init(m, m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 10; j++) {
			int k = i;
			while (k && s[k + 1] != j) {
				k = pre[k];
			}
			if (s[k + 1] == j) {
				k++;
			}
			if (k != m) {
				origin.a[k][i]++;
			}
		}
	}
	ans.n = m;
	ans.m = 1;
	ans.a[0][0] = 1;
	ans = pow(origin, n) * ans;
	int r = 0;
	for (int i = 0; i < m; i++) {
		r += ans.a[i][0];
		r %= mod;
	}
	printf("%d\n", r);
	return 0;
}
