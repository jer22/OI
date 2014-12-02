#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int arr[110][110];
int dp[110][110];
int main() {
	freopen("1387.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	int maxans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!arr[i][j]) dp[i][j] = 0;
			else dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
			maxans = max(maxans, dp[i][j]);
		}
	}
	printf("%d\n", maxans);
	return 0;
}
