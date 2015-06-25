#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
long long K, p;
long long hash[200005], divs[205], cnt = 0;;
long long val[205][205];
long long f[205][205], dp[205][205];

long long gcd(long long a, long long b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int main() {
	freopen("2614.in", "r", stdin);
	scanf("%d %d", &n, &m);
	scanf("%lld %lld", &K, &p);
	for (int i = 1; i <= K; i++) {
		if (K % i) continue;
		divs[++cnt] = i;
		hash[i] = cnt;
	}
	long long t ;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%lld", &t);
			val[i][hash[gcd(t, K)]]++;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= cnt; j++)
			f[i][j] = val[i][j];
	for (int i = 2; i < n; i++) {
		for (int j = 1; j <= cnt; j++) {
			for (int k = 1; k <= cnt; k++) {
				long long t = hash[gcd(divs[j] * divs[k], K)];
				if (j == k) f[i][t] += val[i][j] * (val[i][j] - 1);
				else f[i][t] += val[i][j] * val[i][k];
				f[i][j] %= p;
			}
		}
	}
	for (int j = 1; j <= cnt; j++) dp[1][j] = f[1][j];
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= cnt; j++) {
			for (int k = 1; k <= cnt; k++) {
				long long t = hash[gcd(divs[j] * divs[k], K)];
				dp[i + 1][t] += dp[i][j] * f[i + 1][k] % p;
				dp[i + 1][t] %= p;
			}
		}
	}
	cout << dp[n][cnt] % p << endl;


	return 0;
}
