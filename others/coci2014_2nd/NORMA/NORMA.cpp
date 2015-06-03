#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int MOD = 1000000000;
const int MAXN = 500005;
const int INF = 0x3f3f3f3f;

int n;
long long arr[MAXN];
long long sum[MAXN];

long long solve(int l, int r) {
	if (l > r) return 0;
	long long mx = 0, idx;
	for (int i = l; i <= r; i++)
		if (arr[i] > mx) mx = arr[idx = i];
	long long ans = mx * mx % MOD;
	int f = idx, b = idx;
	long long mi = mx;
	while (f > l && b < r) {
		if (arr[b + 1] > arr[f - 1]) {
			mi = min(mi, arr[++b]);
			long long t = sum[b - f + 1] - sum[b - idx];
			ans += mx * mi % MOD * t % MOD;
		} else {
			mi = min(mi, arr[--f]);
			long long t = sum[b - f + 1] - sum[idx - f];
			ans += mx * mi % MOD * t % MOD;
		}
	}
	while (f > l) {
		mi = min(mi, arr[--f]);
		long long t = sum[b - f + 1] - sum[idx - f];
		ans += mx * mi % MOD * t % MOD;
	}
	while (b < r) {
		mi = min(mi, arr[++b]);
		long long t = sum[b - f + 1] - sum[b - idx];
		ans += mx * mi % MOD * t % MOD;
	}
	ans += solve(l, idx - 1);
	ans += solve(idx + 1, r);
	return ans;
}

int main() {
	freopen("NORMA.in", "r", stdin);
	for (int i = 1; i <= 500000; i++)
		sum[i] = (sum[i - 1] + i) % MOD;
	int fuck();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	if (n <= 5000) return fuck();
	long long ans = solve(1, n);
	cout << ans % MOD << endl;
	return 0;
}

int fuck() {
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		long long l = 0;
		long long mi = 0x3f3f3f3f;
		long long ma = -1;
		for (int j = i; j <= n; j++) {
			l++;
			mi = min(mi, arr[j]);
			ma = max(ma, arr[j]);
			ans += (l * (mi * ma) % MOD) % MOD;
		}
	}
	cout << ans % MOD << endl;
	return 0;
}
