#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXMN 55

using namespace std;

int n, m;
int score[MAXMN][MAXMN];
int dp[MAXMN][MAXMN][MAXMN][MAXMN];
int main() {
	freopen("pid400.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &score[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 1; k <= n; k++) {
				for (int l = 1; l <= m; l++) {
					int t = max(max(dp[i - 1][j][k - 1][l], dp[i][j - 1][k][l - 1]),
						max(dp[i - 1][j][k][l - 1], dp[i][j - 1][k - 1][l]));
					if (i == k && j == l) {
						dp[i][j][k][l] = t + score[i][j];
					} else {
						dp[i][j][k][l] = t + score[i][j] + score[k][l];
					}
				}
			}
		}
	}
	printf("%d\n", dp[n][m][n][m]);
	return 0;
}
