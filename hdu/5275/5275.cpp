#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const long long MOD = 1000000007;

long long read() {
	long long x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

int n, q;
long long x[3005], y[3005];
long long c[3005][3005];
long long inv[250005];
long long powmod(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ans;
}

void init() {
	for (int i = 0; i <= 250000; i++)
		inv[i] = powmod(i, MOD - 2);
	for (int j = 0; j < n; j++) {
		for (int i = 0; i + j < n; i++) {
			if (!j) c[i][i + j] = y[i];
			else if (x[i + j] > x[i]) c[i][i + j] = (c[i + 1][i + j] - c[i][i + j - 1] + MOD) % MOD * inv[x[i + j] - x[i]] % MOD;
			else c[i][i + j] = (c[i][i + j - 1] - c[i + 1][i + j] + MOD) % MOD * inv[-x[i + j] + x[i]] % MOD;
		}
	}
}

long long calc(int l, int r, long long xx) {
	long long ans = 0, t = 1;
	for (int i = l; i <= r; i++) {
		ans = (ans + c[l][i] * t % MOD) % MOD;
		t = t * (xx - x[i] + MOD) % MOD;
	}
	return ans;
}

int main() {
	n = read();
	for (int i = 0; i < n; i++) {
		x[i] = read();
		y[i] = read();
	}
	init();
	q = read();
	int l, r, xx;
	for (int i = 0; i < q; i++) {
		l = read();
		r = read();
		xx = read();
		printf("%I64d\n", calc(l - 1, r - 1, xx));
	}
	return 0;
}
