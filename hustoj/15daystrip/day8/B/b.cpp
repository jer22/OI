#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int l, r;

long long sum[70], tot[70];
void init() {
	for (int i = 1; i <= 64; i++) {
		tot[i] = tot[i - 1] * 2ll + (1ll << (i - 1));
		// sum[i] = sum[i - 1] + tot[i];
	}
}

int n, dig[70], num[70];

long long dfs(int idx) {
	if (idx == 0) return dig[0];
	long long ans = 0;
	if (dig[idx]) {
		ans += tot[idx];
		ans += num[idx - 1] + 1;
	}
	ans += dfs(idx - 1);
	return ans;
}

long long solve(int x) {
	if (!x) return 0;
	n = 0;
	while (x) {
		dig[n++] = (x & 1);
		x >>= 1;
	}
	num[0] = dig[0];
	for (int i = 1; i < n; i++)
		num[i] = num[i - 1] + dig[i] * (1 << i);
	long long ans = dfs(n - 1);

	return ans;
}

int main() {
	freopen("b.in", "r", stdin);
	init();
	// cout << tot[3] << endl;
	int cas = 0;
	while (~scanf("%d %d", &l, &r)) {
		if (!l && !r) break;
		cas++;
		long long a = solve(r);
		long long b = 0;
		if (l) b = solve(l - 1);
		printf("Case %d: %lld\n", cas, a - b);
	}


	return 0;
}
