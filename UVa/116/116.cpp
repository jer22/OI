#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int arr[110][110];
int dp[110][110];
int pre[110][110];
int n, m;

int getfir(int i) {
	int fir = i;
	for (int j = m; j >= 2; j--) {
		fir = pre[fir][j];
	}
	return fir;
}

void print(int i, int j) {
	if (j == 1) {
		printf("%d", i);
		return;
	}
	print(pre[i][j], j - 1);
	printf(" %d", i);
}

int main() {
	freopen("116.in", "r", stdin);
	while (scanf("%d %d", &n, &m) != EOF) {
		memset(arr, 0, sizeof(arr));
		memset(pre, 0, sizeof(pre));
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				dp[i][j] = INF;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &arr[i][j]);
			}
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				int t = j - 1;
				if (!t) t = n;
				if (dp[i - 1][t] + arr[j][i] < dp[i][j]) {
					dp[i][j] = dp[i - 1][t] + arr[j][i];
					pre[j][i] = t;
				}
				if (t == n) {
					if (dp[i - 1][j] + arr[j][i] <= dp[i][j]) {
						dp[i][j] = dp[i - 1][j] + arr[j][i];
						pre[j][i] = j;
					}
				} else {
					if (dp[i - 1][j] + arr[j][i] < dp[i][j]) {
						dp[i][j] = dp[i - 1][j] + arr[j][i];
						pre[j][i] = j;
					}
				}
				
				t = j + 1;
				if (t > n) t = 1;
				if (t == 1) {
					if (dp[i - 1][t] + arr[j][i] <= dp[i][j]) {
						dp[i][j] = dp[i - 1][t] + arr[j][i];
						pre[j][i] = t;
					}
				} else {
					if (dp[i - 1][t] + arr[j][i] < dp[i][j]) {
						dp[i][j] = dp[i - 1][t] + arr[j][i];
						pre[j][i] = t;
					}
				}	
			}
		}
		int idx = 1;
		int minn = INF;
		int fir;
		for (int i = 1; i <= n; i++) {
			if (dp[m][i] < minn) {
				idx = i;
				minn = dp[m][i];
				fir = getfir(i);
			} else if (dp[m][i] == minn) {
				int f = getfir(i);
				if (f < fir) {
					fir = f;
					idx = i;
				}
			}
		}
		printf("%d\n", dp[m][idx]);
		print(idx, m);
		printf("\n");
	}


	return 0;
}
