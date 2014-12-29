#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n, m;
int arr[150][150];
int dp[150][150];
int main() {
	freopen("1978.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &arr[i][j]);
		memset(dp, 0, sizeof(dp));
		dp[1][1] =  1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (!dp[i][j]) continue;
				for (int k = 0; k <= arr[i][j]; k++) {
					for (int l = 0; k + l <= arr[i][j]; l++) {
						if (!k && !l) continue;
						dp[i + k][j + l] += dp[i][j];
						dp[i + k][j + l] %= 10000;
					}
				}
			}
		}
		cout << dp[n][m] << endl;
	}


	return 0;
}
