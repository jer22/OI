#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 10000005;

int T, n, m;
int mob[MAXN];
int pri[MAXN], p[MAXN], num = 0;
long long g[MAXN];

void init() {
	p[1] = 1;
	mob[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		if (pri[i]) continue;
		for (int j = i + i; j < MAXN; j += i) {
			pri[j] = 1;
			p[j] = i;
		}
	}
	for (int i = 2; i < MAXN; i++) {
		mob[i] = pri[i] ? (i / p[i] % p[i] ? -mob[i / p[i]] : 0) : -1;
	}
	for (int i = 2; i < MAXN; i++) {
		if (pri[i]) continue;
		for (int j = i; j < MAXN; j += i) {
			g[j] += (long long)mob[j / i];
		}
	}
	for (int i = 1; i < MAXN; i++)
		g[i] += g[i - 1];
}

int main() {
	freopen("2820.in", "r", stdin);
	cin >> T;
	init();
	while (T--) {
		scanf("%d %d", &n, &m);
		if (n > m) swap(n, m);
		long long ans = 0;
		for (int i = 1, pos; i <= n; i = pos + 1) {
			pos = min(n / (n / i), m / (m / i));
			ans += (g[pos] - g[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", ans);
	}

	return 0;
}
