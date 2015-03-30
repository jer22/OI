#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
int dp[205][8];
int main() {
	freopen("1039.in", "r", stdin);
	cin >> n >> k;
	for (int i = 0; i <= k; i++)
			dp[i][i] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= min(k, i - 1); j++) {
			for (int t = 1; t <= min(j, i - j); t++) {
				dp[i][j] += dp[i - j][t];
			}
		}
	}
	cout << dp[n][k] << endl;


	return 0;
}
