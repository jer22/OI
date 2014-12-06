/*
ID:shijiey1
PROG:tour
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int n, v;
map<string, int> city;
string name[105];
int arr[105][105];
int dp[105][105];
int main() {
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
	scanf("%d %d", &n, &v);
	string sa, sb;
	for (int i = 1; i <= n; i++) {
		cin >> sa;
		city[sa] = i;
		name[i] = sa;
	}
	for (int i = 1; i <= v; i++) {
		cin >> sa >> sb;
		arr[city[sa]][city[sb]] = 1;
		arr[city[sb]][city[sa]] = 1;
	}
	arr[n][n] = 1;
	dp[1][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!dp[i][j]) continue;
			for (int k = max(i, j) + 1; k <= n; k++) {
				if (arr[j][k]) dp[i][k] = max(dp[i][k], dp[i][j] + 1);
			}
			for (int k = max(i, j) + 1; k <= n; k++) {
				if (arr[i][k]) dp[k][j] = max(dp[k][j], dp[i][j] + 1);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (arr[i][n] && arr[j][n]) {
				// cout << i << ' ' << j << ' ' << dp[i][j] << endl;
				ans = max(ans, dp[i][j] + 1);
			}
			// cout << dp[i][j] << "   ";
		}
		// cout << endl;
	}
	cout << ans << endl;
	return 0;
}
