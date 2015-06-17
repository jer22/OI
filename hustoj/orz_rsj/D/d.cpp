#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int n;
long long arr[MAXN];
long long dp[MAXN];
int main() {
	// freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%I64d", &arr[i]);
	dp[1] = 0;
	dp[2] = abs(arr[1] - arr[2]);
	for (int i = 3; i <= n; i++) {
		long long val = abs(arr[i] - arr[i - 1]);
		dp[i] = max(dp[i - 1], dp[i - 2] + val);
		if (arr[i] >= arr[i - 1] && arr[i - 1] >= arr[i - 2] || arr[i] <= arr[i - 1] && arr[i - 1] <= arr[i - 2	])
			dp[i] = max(dp[i], dp[i - 1] + val);
	}
	printf("%I64d\n", dp[n]);
	return 0;
}
