#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int dp[255][255];
int arr[255];
int main() {
	freopen("input", "r", stdin);
	cin >> n;
	char c;
	getchar();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c = getchar();
			dp[i][j] = c == '1';
		}
		getchar();
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!dp[i][j]) continue;
			else dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			arr[dp[i][j]]++;
		}
	}
	for (int i = n; i >= 1; i--)
		arr[i] += arr[i + 1];
	for (int i = 2; i <= n; i++) {
		if (arr[i]) printf("%d %d\n", i, arr[i]);
	}
	if (!arr[2]) printf("No\n");

	return 0;
}
