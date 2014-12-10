/*
ID:shijiey1
PROG:tour
LANG:C++
*/

/*
可以看做从起点出发走两条线到终点。
dp[i][j]表示第一条线走到i,第二条线走到j的最多经过的城市数。
枚举max(i,j)之后的每一个城市k，下一步可以i走到k也可以j走到k。
dp[i][k] = max(dp[i][k], dp[i][j] + 1)
dp[k][j] = max(dp[k][j], dp[i][j] + 1)
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
				ans = max(ans, dp[i][j] + 1);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
