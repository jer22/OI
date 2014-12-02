/*
ID:shijiey1
LANG:C++
PROG:nuggets
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[11];
int limit;
int dp[69050];
int main() {
	freopen("nuggets.in", "r", stdin);
	freopen("nuggets.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	arr[0] = 1;
	limit = arr[n] * arr[n - 1] + 10;
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = arr[i]; j <= limit; j++) {
			if (dp[j - arr[i]]) dp[j] = 1;
		}
	}
	for (int i = limit; i >= 1; i--) {
		if (!dp[i]) {
			if (i >= limit - 10) {
				printf("0\n");
				return 0;
			} else {
				printf("%d\n", i);
			}
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
