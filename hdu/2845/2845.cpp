#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[200011];
int brr[200011];
int dp[200011];
int DP() {
	memset(dp, 0, sizeof(dp));
	dp[1] = arr[1];
	dp[2] = arr[2];
	for (int i = 3; i <= m; i++)
		dp[i] = max(dp[i], max(dp[i - 2] + arr[i], dp[i - 3] + arr[i]));
	return max(dp[m], dp[m - 1]);
}

int main() {
	freopen("2845.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				scanf("%d", &arr[j]);
			brr[i] = DP();
		}
		memset(dp, 0, sizeof(dp));
		dp[1] = brr[1];
		dp[2] = brr[2];
		for (int i = 3; i <= n; i++)
			dp[i] = max(dp[i], max(dp[i - 2] + brr[i], dp[i - 3] + brr[i]));
		cout << max(dp[n], dp[n - 1]) << endl;
	}
	return 0;
}
