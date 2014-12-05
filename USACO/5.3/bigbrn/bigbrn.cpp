/*
ID:shijiey1
LANG:C++
PROG:bigbrn
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, t;
int arr[1005][1005];
int dp[1005][1005];
int main() {
	freopen("bigbrn.in", "r", stdin);
	freopen("bigbrn.out", "w", stdout);
	cin >> n >> t;
	int a, b;
	for (int i = 0; i < t; i++) {
		cin >> a >> b;
		arr[a][b] = 1;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!arr[i][j])
				dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
			else dp[i][j] = 0;
			ans = max(ans, dp[i][j]);
		}
	}
	cout << ans << endl;
	return 0;
}
