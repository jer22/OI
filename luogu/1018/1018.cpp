#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 42

using namespace std;

int n, k;
int arr[MAXN];
int dp[MAXN][MAXN][7];

void initNum() {
	for (int i = 0; i < n; i++) {
		dp[i][i][0] = arr[i];
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			dp[i][j][0] = dp[i][j - 1][0] * 10 + arr[j];
		}
	}
}

int main() {
	freopen("1018.in", "r", stdin);
	scanf("%d %d\n", &n, &k);
	char c;
	for (int i = 0; i < n; i++) {
		scanf("%c", &c);
		arr[i] = c - '0';
	}
	initNum();
	for (int k = 1; k <= n - 1; k++) {
		for (int i = 0; i < n - k - 1; i++) {
			for (int j = i + k; j < n; j++) {
				for (int l = i; l < j; l++) {
				 	dp[i][j][k] = max(dp[i][j][k], dp[i][l][0] * dp[l + 1][j][k - 1]);
				 	// printf("%d|%d|%d|%d\n", i, j, k, dp[0][2][2]);
				 }
			}
		}

	}
	// for (int i = 0; i < n - 1; i++) {
	// 	for (int j = i; j < n; j++) {
	// 		for (int k = 0; k <= j - i; k++) {
	// 			printf("%d|%d|%d|%d ", i, j, k, dp[i][j][k]);
	// 		}
	// 		printf("\n");
	// 	}
	// 	printf("\n");
	// }
	printf("%d\n", dp[0][n - 1][k]);
	return 0;
}
