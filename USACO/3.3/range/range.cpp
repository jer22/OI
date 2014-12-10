/*
ID:shijiey1
PROG:range
LANG:C++
*/

/*
dp[i][j]：以点(i,j)为右下角能取到的最大正方形的边长
若arr[i][j]==0,则dp[i][j]=0
否则dp[i][j]=min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[258][258];
int dp[258][258];
int ans[258];
int main() {
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);
	scanf("%d\n", &n);
	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%c", &c);
			arr[i][j] = c - '0';
		}
		getchar();
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!arr[i][j]) dp[i][j] = 0;
			else dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
			if (dp[i][j] > 1);
				ans[dp[i][j]]++;
		}
	}
	for (int i = 2; i <= n; i++) {
		int re = 0;
		for (int j = i; j <= n; j++) {
			re += ans[j];
		}
		if (re)
			printf("%d %d\n", i, re);
	}
	return 0;
}
