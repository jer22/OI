#include <cstdio>
#include <algorithm>
 
using namespace std;
 
const int MAXN = 10000005;
const long long MOD = 20101009ll;
const long long inv = 10050505ll;
 
 
long long Sum(long long a, long long b) {
	a = a * (a + 1) % MOD;
	b = b * (b + 1) % MOD;
	return ((a * b % MOD) * inv % MOD) * inv % MOD;
}
long long n, m;
long long mob[MAXN], p[1000000], check[MAXN], tot;
long long f[MAXN];
void getMob() {
	mob[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!check[i]) {
			p[++tot] = i;
			mob[i] = -1;
		}
		for (int j = 1; j <= tot; j++) {
			if (i * p[j] > n) break;
			check[i * p[j]] = 1;
			if (i % p[j] == 0) {
				mob[i * p[j]] = 0;
				break;
			}
			else mob[i * p[j]] = -mob[i];
		}
	}
	f[0] = 0;
	for (int i = 1; i <= n; i++)
		f[i] = (f[i - 1] + (mob[i] * i % MOD * i % MOD)) % MOD;
}
 
int main() {
	freopen("2154.in", "r", stdin);
	scanf("%lld %lld", &n, &m);
	if (n > m) swap(n, m);
	getMob();
	long long ans = 0;
	for (long long d = 1, pos1; d <= n; d = pos1 + 1) {
		pos1 = min(n / (n / d), m / (m / d));
		long long nn = n / d;
		long long mm = m / d;
		long long tmp = 0;
		for (long long k = 1, pos2; k <= nn; k = pos2 + 1) {
			pos2 = min(nn / (nn / k), mm / (mm / k));
			(tmp += (((f[pos2] - f[k - 1] + MOD) % MOD) * (Sum(nn / k, mm / k) % MOD)) % MOD) %= MOD;
		}
		(ans += ((((d + pos1) * (pos1 - d + 1)) / 2) % MOD * tmp) % MOD) %= MOD;
	}
	printf("%lld\n", ans);
 
 
	return 0;
}