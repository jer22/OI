#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <complex>

#define pi acos(-1)
#define E complex<double>

using namespace std;

const int MAXN = 150005;

int n, m, L;
char str[MAXN];
int r[MAXN], c[MAXN];
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
	freopen("2179.in", "r", stdin);
	scanf("%d", &n);
	n--;
	scanf("%s", str);
	for (int i = 0; i <= n; i++)
		a[i] = str[n - i] - '0';
	scanf("%s", str);
	for (int i = 0; i <= n; i++)
		b[i] = str[n - i] - '0';
	m = n << 1;
	for (n = 1; n <= m; n <<= 1) L++;
	for (int i = 0; i < n; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));
	fft(a, 1);
	fft(b, 1);
	for (int i = 0; i < n; i++) a[i] *= b[i];
	fft(a, -1);
	for (int i = 0; i <= m; i++) c[i] = (int)(a[i].real() + 0.1);
	for (int i = 0; i <= m; i++)
		cout << i << ' ' << c[i] << endl;
	for (int i = 0; i <= m; i++) {
		if (c[i] >= 10) {
			c[i + 1] += c[i] / 10;
			c[i] %= 10;
			if (i == m) m++;
		}
	}
	for (int i = m; i >= 0; i--) printf("%d", c[i]);
	printf("\n");
	return 0;
}
