#include <bits/stdc++.h>

#define pi acos(-1)
#define E complex<double>

using namespace std;

const int MAXN = 100005;
const long long MOD = 1000000007;

int r[MAXN << 3], c[MAXN << 3];
E a[MAXN << 3], b[MAXN << 3];
int bi[MAXN << 3];

void fft(E *a, int f, int n) {
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

char ss[MAXN << 1];
int p[MAXN << 1];
int manacher(char s[MAXN], int n) {
	int re = 0;
	ss[0] = '$', ss[1] = '#';
	for (int i = 1; i <= n; i++)
		ss[i << 1] = s[i], ss[i << 1 | 1] = '#';
	n = n << 1 | 1;
	int mx = 1, id = 1;
	for (int i = 1; i <= n; i++) {
		p[i] = min(p[id + id - i], mx - i);
		while (ss[i + p[i]] == ss[i - p[i]])
			p[i]++;
		if (p[i] + i > mx)
			mx = p[i] + i, id = i;
		re += p[i] >> 1, re %= MOD;
	}
	return re;
}

int n;
char s[MAXN];
int main() {
	freopen("3160.in", "r", stdin);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = (s[i] == 'a');
		b[i] = (s[i] == 'b');
	}
	int t = n - 1, L = 0;
	int m = t << 1;
	for (t = 1; t <= m; t <<= 1) L++;
	bi[0] = 1;
	for (int i = 1; i < t; i++) bi[i] = (bi[i - 1] << 1) % MOD;
	for (int i = 0; i < t; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));
	fft(a, 1, t), fft(b, 1, t);
	for (int i = 0; i < t; i++)
		a[i] *= a[i], b[i] *= b[i];
	fft(a, -1, t), fft(b, -1, t);
	long long ans = 0;
	for (int i = 0; i < t; i++) {
		c[i] = ((int)(a[i].real() + 0.1) + 1 >> 1) + ((int)(b[i].real() + 0.1) + 1 >> 1);
		(((ans += bi[c[i]] - 1) %= MOD) += MOD) %= MOD;
	}
	((ans -= manacher(s, n)) += MOD) %= MOD;
	printf("%lld\n", ans);

	return 0;
}
