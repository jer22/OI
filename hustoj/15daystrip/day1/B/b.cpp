#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <complex>

#define E complex<double>
#define pi acos(-1)

using namespace std;

const int MAXN = 500005;
const int MOD = 313;

int n, m, L;
int arr[MAXN];

int c[MAXN];
E a[MAXN], b[MAXN];

void fft(E *a, int f, int len) {
	for (int i = 0; i < len; i++)
		if (i < c[i]) swap(a[i], a[c[i]]);
	for (int i = 1; i < len; i <<= 1) {
		E wn(cos(pi / i), f * sin(pi / i));
		for (int j = 0; j < len; j += (i << 1)) {
			E w(1, 0);
			for (int k = 0; k < i; k++, w *= wn) {
				E x = a[j + k];
				E y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}

	if (f == -1) for (int i = 0; i < len; i++) a[i] /= len;
}

int dp[MAXN];
void solve(int l, int r) {
	if (l == r) {
		(dp[l] += arr[l]) %= MOD;
		return;
	}
	int mid = l + r >> 1;
	solve(l, mid);


	int p = mid - l;

	m = p << 1;
	L = 0;
	for (p = 1; p <= m; p <<= 1) L++;
	for (int i = 0; i <= p; i++)
		a[i] = b[i] = E(0, 0);
	for (int i = l; i <= mid; i++) {
		a[i - l] = dp[i];
	}
	for (int i = 0; i <= r - l; i++) {
		b[i] = arr[i];
	}
	// memset(c, 0, sizeof(c));
	for (int i = 0; i <= p; i++)
		c[i] = (c[i >> 1] >> 1) | ((i & 1) << (L - 1));
	fft(a, 1, p);
	fft(b, 1, p);
	for (int i = 0; i <= p; i++) {
		a[i] *= b[i];
	}
	if (r == 2) {
		// for (int i = 0; i <= p; i++)
		// 	cout << a[i].real() << endl;
	}
	fft(a, -1, p);
	for (int i = mid + 1; i <= r; i++) {
		(dp[i] += (int)(a[i - l - 1].real() + 0.1)) %= MOD;
	}
	solve(mid + 1, r);
}

int main() {
	freopen("b.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
		}
		solve(0, n - 1);
		cout << dp[n - 1] << endl;
	}

	return 0;
}
