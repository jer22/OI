#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 60

using namespace std;

int n, K;
int dp1[MAXN][MAXN][12];
int dp2[MAXN][MAXN][12];
int arr[MAXN];

int mod(int a) {
	if (a >= 0)
		return a % 10;
	return mod(a + 10);
}

int main() {
	freopen("1043.in", "r", stdin);
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	// 预处理dp[i][j][1]
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int l = 0; l < j; l++) {
				dp1[i][j][1] += arr[(i + l - 1) % n + 1];
				dp2[i][j][1] += arr[(i + l - 1) % n + 1];
			}
			dp1[i][j][1] = mod(dp1[i][j][1]);
			dp2[i][j][1] = mod(dp2[i][j][1]);

		}
	}
	for (int k = 2; k <= K; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = (i + k - 2) % n + 1; j <= n; j++) {
				for (int l = 1; l <= j - 1; l++) {
					dp1[i][j][k] = max(dp1[i][j][k], dp1[i][l][1] * dp1[(i + l - 1) % n + 1][j - l][k - 1]);
					if (dp2[i][j][k])
						dp2[i][j][k] = min(dp2[i][j][k], dp2[i][l][1] * dp2[(i + l - 1) % n + 1][j - l][k - 1]);
					else dp2[i][j][k] = dp2[i][l][1] * dp2[(i + l - 1) % n + 1][j - l][k - 1];
				}
			}
		}
	}
	int maxans = 0;
	int minans = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		minans = min(minans, dp2[i][n][K]);
		maxans = max(maxans, dp1[i][n][K]);
	}
	printf("%d\n%d\n", minans, maxans);
	return 0;
}
