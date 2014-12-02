#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 355
#define MAX_CARD 42

using namespace std;

int score[MAXN];
int dp[MAX_CARD][MAX_CARD][MAX_CARD][MAX_CARD];
int n, m;
int maxUsed[4];
int main( void ) {
	int t;
	freopen("pid599.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &score[i]);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &t);
		maxUsed[t - 1]++;
	}
	int step = 0;
	for (int a = 0; a <= maxUsed[0]; a++) {
		for (int b = 0; b <= maxUsed[1]; b++) {
			for (int c = 0; c <= maxUsed[2]; c++) {
				for (int d = 0; d <= maxUsed[3]; d++) {
					step = a + b * 2 + c * 3 + d * 4 + 1;
					if (a + 1 <= maxUsed[0] && step + 1 <= n) {
						dp[a + 1][b][c][d] = max(dp[a][b][c][d] + score[step + 1], dp[a + 1][b][c][d]);
					}
					if (b + 1 <= maxUsed[1] && step + 2 <= n) {
						dp[a][b + 1][c][d] = max(dp[a][b][c][d] + score[step + 2], dp[a][b + 1][c][d]);
					}
					if (c + 1 <= maxUsed[2] && step + 3 <= n) {
						dp[a][b][c + 1][d] = max(dp[a][b][c][d] + score[step + 3], dp[a][b][c + 1][d]);
					}
					if (d + 1 <= maxUsed[3] && step + 4 <= n) {
						dp[a][b][c][d + 1] = max(dp[a][b][c][d] + score[step + 4], dp[a][b][c][d + 1]);
					}
				}
			}
		}
	}
	printf("%d\n", dp[maxUsed[0]][maxUsed[1]][maxUsed[2]][maxUsed[3]] + score[1]);
	return 0;
}
