#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <complex>

#define pi acos(-1)
#define E complex<double>
#define MAXN 300005

using namespace std;

int n, m, L;
int r[MAXN];
E f[MAXN], g[MAXN], h[MAXN];
E c[MAXN], d[MAXN];

void fft(E *a, int f) {
	for (int i = 0; i < n; i++)
		if (i < r[i]) swap(a[i], a[r[i]]);
	for (int i = 1; i < n; i <<= 1) {
		E wn(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < n; j += (i << 1)) {
			E w(1, 0);
			for (int k = 0; k < i; k++, w *= wn) {
				E x = a[j + k];
				E y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
	if (f == -1)
		for (int i = 0; i < n; i++) a[i] /= n;
}

int main() {
	freopen("3527.in", "r", stdin);
	scanf("%d", &n);
	n--;
	double x;
	for (int i = 0; i <= n; i++) {
		scanf("%lf", &x);
		f[i] = g[n - i] = x;
	}
	for (int i = 1; i <= n; i++)
		h[i] = 1.0 / i / i;
	m = n << 1;
	for (n = 1; n <= m; n <<= 1) L++;
	for (int i = 0; i < n; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));
	fft(f, 1);
	fft(g, 1);
	fft(h, 1);
	for (int i = 0; i < n; i++) {
		c[i] = f[i] * h[i];
		d[i] = g[i] * h[i];
	}
	fft(c, -1);
	fft(d, -1);
	for (int i = 0; i <= m / 2; i++) {
		printf("%.3lf\n", c[i].real() - d[m / 2 - i].real());
	}

	return 0;
}
	