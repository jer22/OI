/*
ID:shijiey1
LANG:C++
PROG:theme
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[5010];
int theme[5010];
int dp[2][5010];
int main() {
	freopen("theme.in", "r", stdin);
	freopen("theme.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	arr[0] = 0x3f3f3f3f;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (arr[i] - arr[j] == arr[i - 1] - arr[j - 1] && i - dp[(i % 2) ^ 1][j - 1] - 1 > j) {
				dp[i % 2][j] = max(dp[i % 2][j], dp[(i % 2) ^ 1][j - 1] + 1);
				ans = max(ans, dp[i % 2][j]);
			}
		}
		memset(dp[(i % 2) ^ 1], 0, sizeof(dp[(i % 2) ^ 1]));
	}
	if (ans < 4) {
		cout << 0 << endl;
	} else {
		cout << ans + 1 << endl;
	}
	return 0;
}
