#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int stat[105];
int dp[105][3];
int main() {
	// freopen("c.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> stat[i];
	if (stat[1] == 1) dp[1][1] = 1;
	else if (stat[1] == 2) dp[1][2] = 1;
	else if (stat[1] == 3) dp[1][1] = dp[1][2] = 1;
	for (int i = 2; i <= n; i++) {
		dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][2]));
		if (stat[i] == 1 || stat[i] == 3) {
			dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + 1;
		}
		if (stat[i] == 2 || stat[i] == 3) {
			dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + 1;
		}
	}
	int ans = max(dp[n][0], max(dp[n][1], dp[n][2]));
	cout << n - ans << endl;


	return 0;
}
