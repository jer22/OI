#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;

int mob[MAXN];
long long sum[MAXN];
void getMob() {
	for (int i = 1; i <= 50000; i++) {
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= 50000; j += i)
			mob[j] += delta;
	}
	for (int i = 1; i <= 50000; i++)
		sum[i] = sum[i - 1] + mob[i];
}

int k;
long long solve(int n, int m) {
	n /= k, m /= k;
	if (n > m) swap(n, m);
	long long ans = 0;
	for (int i = 1, pos; i <= n; i = pos + 1) {
		pos = min(n / (n / i), m / (m / i));
		ans += (sum[pos] - sum[i - 1]) * (n / i) * (m / i);
	}
	return ans;
}

int main() {
	freopen("2301.in", "r", stdin);
	int T;
	scanf("%d", &T);
	getMob();
	int a, b, c, d;
	while (T--) {
		scanf("%d %d %d %d %d", &a, &b, &c, &d, &k);
		long long ans = solve(b, d) - solve(a - 1, d) - solve(b, c - 1) + solve(a - 1, c - 1);
		printf("%lld\n", ans);
	}

	return 0;
}
