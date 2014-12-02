#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int order[25];
int arr[25];
int dp[25][25];
int main() {
	freopen("111.in", "r", stdin);
	scanf("%d", &n);
	int t;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t);
		order[t] = i;
	}
	while (scanf("%d", &t) != EOF) {
		arr[t] = 1;
		for (int i = 2; i <= n; i++) {
			scanf("%d", &t);
			arr[t] = i;
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (arr[i] == order[j]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				} else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		printf("%d\n", dp[n][n]);
	}	

	return 0;
}
