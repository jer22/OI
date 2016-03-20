#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#pragma comment(linker, "/STACK:102400000,102400000")

using namespace std;

const int MAXN = 200005;
const long long MOD = 1000000007;

int T, n;
vector<int> edges[MAXN];
long long down[MAXN];
long long up[MAXN];

long long exgcd(long long a, long long b, long long &x, long long &y) {
	long long d = a;
	if (b) {
		d = exgcd(b, a % b, y, x);
		y -= (a / b) * x;
	} else {
		x = 1, y = 0;
	}
	return d;
}

long long inv(long long t) {
	// long long x, y;
	// exgcd(t, MOD, x, y);
	// while (x < 0) x += MOD;
	// return x;
	long long ans = 1;
	long long base = t;
	long long b = MOD - 2;
	while (b) {
		if (b & 1) (ans *= base) %= MOD;
		b >>= 1;
		(base *= base) %= MOD;
	}
	return ans;
}

void dfs_down(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs_down(nex, x);
		up[x] = (up[x] * (down[nex] + 1) % MOD + down[x] * up[nex] % MOD) % MOD;
		(down[x] *= (down[nex] + 1)) %= MOD;
	}
}

void dfs_up(int x, int pre) {
	if (x == 1) up[x] = down[x];
	else {
		up[x] = ((up[pre] * inv(down[x] + 1ll) % MOD + 1ll) % MOD * down[x]) % MOD;
	}
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs_up(nex, x);
	}
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			up[i] = down[i] = 1;
		if (n == 1) {
			cout << 1 << endl;
			continue;
		}
		for (int i = 1; i <= n; i++) edges[i].clear();
		int a;
		for (int i = 2; i <= n; i++) {
			scanf("%d", &a);
			edges[i].push_back(a);
			edges[a].push_back(i);
		}
		dfs_down(1, 1);
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			// cout << down[i] << endl;
			(ans += up[i]) %= MOD;
		}
		printf("%lld\n", ans);
	}

	return 0;
}
