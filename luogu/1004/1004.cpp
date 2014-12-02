#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 12

using namespace std;

int n;
int arr[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];
int main() {
	freopen("1004.in", "r", stdin);
	scanf("%d", &n);
	int x, y, num;
	while (true) {
		scanf("%d %d %d", &x, &y, &num);
		if (!x && !y && !num) {
			break;
		}
		arr[x][y] = num;
	}
	for (int a = 1; a <= n; a++) {
		for (int b = 1; b <= n; b++) {
			for (int c = 1; c <= n; c++) {
				for (int d = 1; d <= n; d++) {
					if (a + b != c + d) {
						continue;
					}
					int t = max(max(dp[a - 1][b][c - 1][d], dp[a][b - 1][c][d - 1]),
							max(dp[a - 1][b][c][d - 1], dp[a][b - 1][c - 1][d]));
					if (a == c && b == d) {
						dp[a][b][c][d] = max(dp[a][b][c][d], t + arr[a][b]);
					} else {
						dp[a][b][c][d] = max(dp[a][b][c][d], t + arr[a][b] + arr[c][d]);
					}
				}
			}
		}
	}
	printf("%d\n", dp[n][n][n][n]);
	return 0;
}
