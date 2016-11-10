#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1000005;
const long long MOD = 1000000007;

int T;
long long n;
long long phi[MAXN];
bool vis[MAXN];
long long prime[MAXN], tot = 0;
long long minfac[MAXN];
vector<long long> fac[MAXN];

void init() {
	phi[1] = 1;
	for (int i = 2; i < MAXN - 1; i++) {
		if (!vis[i]) {
			minfac[i] = i;
			prime[++tot] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= tot; j++) {
			if(i * prime[j] > MAXN) break;
			vis[i * prime[j]] = 1;
			minfac[prime[j] * i] = prime[j];
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	for (int i = 2; i < MAXN - 1; i++) {
		int x = i;
		while (x > 1) {
			long long t = minfac[x];
			fac[i].push_back(t);
			while (!(x % t)) x /= t;
		}
	}
}

long long tmp;
bool use[11];
long long cal(int siz, long long num, long long p) {
	long long now = 1;
	for (int i = 0; i < siz; i++) {
		if (use[i]) now *= fac[p][i];
	}
	return num / now;
}
void dfs(int i, int siz, long long p, int cnt, long long num) {
	if (i == siz) {
		if (cnt) {
			tmp += cal(siz, num, p) * ((cnt & 1) ? 1ll : -1ll);
			while (tmp < 0) tmp += MOD;
			tmp %= MOD;
		}
		return;
	}
	dfs(i + 1, siz, p, cnt, num);
	use[i] = 1;
	dfs(i + 1, siz, p, cnt + 1, num);
	use[i] = 0;
}
long long solve(long long p, long long num) {
	tmp = 0;
	int siz = fac[p].size();
	memset(use, 0, sizeof(use));
	dfs(0, siz, p, 0, num);
	return (num - tmp + MOD) % MOD;
}

int main() {
	// freopen("5942.in", "r", stdin);
	scanf("%d", &T);
	init();
	for (int cas = 1; cas <= T; cas++) {
		scanf("%lld", &n);
		long long ans = 0;
		for (long long p = 1; p * p < n; p++) {
			ans += solve(p, n / p) - phi[p];
			while (ans < 0) ans += MOD;
			ans %= MOD;
		}
		ans = (ans * 2ll + 1ll) % MOD;
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}
