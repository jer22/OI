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
E a[MAXN], b[MAXN];

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
	if (f == -1) for (int i = 0; i < n; i++) a[i] /= n;
}

int main() {
	freopen("2194.in", "r", stdin);
	scanf("%d", &n);
	n--;
	int x, y;
	for (int i = 0; i <= n; i++) {
		scanf("%d %d", &x, &y);
		a[i] = x;
		b[n - i] = y;
	}
	m = n << 1;
	for (n = 1; n <= m; n <<= 1) L++;
	for (int i = 0; i < n; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));
	fft(a, 1);
	fft(b, 1);
	for (int i = 0; i <= n; i++) a[i] *= b[i];
	fft(a, -1);
	for (int i = m / 2; i <= m; i++)
		printf("%d\n", (int)(a[i].real() + 0.1));

	return 0;
}
