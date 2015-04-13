#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <iostream>

using namespace std;

const long long INF = LONG_LONG_MAX;

int n, p;
long long arr[1005];
long long dp[1005][1005][2];

long long cal(int l, int r, int id) {
	return id ? arr[r] : arr[l];
}

long long dfs(int l, int r, int pos) {
	if (l == 1 && r == n) return 0;
	if (dp[l][r][pos] != INF) return dp[l][r][pos];
	long long best = INF;
	if (l - 1 >= 1) best = min(best, dfs(l - 1, r, 0) + (cal(l, r, pos) - arr[l - 1]) * (n - (r - l + 1)));
	if (r + 1 <= n) best = min(best, dfs(l, r + 1, 1) + (arr[r + 1] - cal(l, r, pos)) * (n - (r - l + 1)));
	return dp[l][r][pos] = best;
}

int main() {
	// freopen("1694.in", "r", stdin);
	scanf("%d %d", &n, &p);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	arr[++n] = p;
	sort(arr + 1, arr + n + 1);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			dp[i][j][0] = dp[i][j][1] = LONG_LONG_MAX;
	int st;
	for (st = 1; st <= n; st++)
		if (arr[st] == p) break;
	long long ans = dfs(st, st, 0);
	cout << ans << endl;

	return 0;
}
