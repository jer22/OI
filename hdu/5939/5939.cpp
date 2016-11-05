#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 2005;

int T, n, m;
char s[MAXN][MAXN];
int arr[MAXN];
short sum[MAXN][MAXN];

void init() {
	for (int i = 0; i <= 2000; i++)
		for (int j = 0; j <= 2000; j++)
			sum[i][j] = 32000;
	sum[0][0] = 0;
	sum[1][1] = 1;
	for (int i = 1; i <= 2000; i++)
		sum[0][i] = sum[i][0] = i + 1 >> 1;
	for (int i = 0; i < 2000; i++) {
		for (int j = 0; j < 2000; j++) {
			sum[i + 1][j + 2] = min(sum[i + 1][j + 2], short(sum[i][j] + 1));
			sum[i + 2][j + 1] = min(sum[i + 2][j + 1], short(sum[i][j] + 1));
		}
	}
}

int dp[2][MAXN];
int main() {
	freopen("5939.in", "r", stdin);
	init();
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= m; i++)
			arr[i] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%s", s[i] + 1);
			for (int j = 1; j <= m; j++)
				if (!arr[j] && s[i][j] == '*')
					arr[j] = n - i + 1;
		}
		for (int i = 0; i <= arr[1]; i++)
			dp[1][i] = sum[arr[1] - i][0];
		for (int i = 2; i <= m; i++) {
			for (int j = 0; j <= arr[i]; j++)
				dp[i & 1][j] = 0x3f3f3f3f;
			int pre = 0;
			for (int j = 0; j <= arr[i]; j++) {
				for (int k = pre; k <= arr[i - 1]; k++) {
					int nw = dp[(i + 1) & 1][k] + sum[k][arr[i] - j];
					if (nw < dp[i & 1][j]) {
						dp[i & 1][j] = nw;
						pre = k;
					}
				}
			}
		}
		printf("Case #%d: %d\n", cas, dp[m & 1][0]);
	}


	return 0;
}
