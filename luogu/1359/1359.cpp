#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[210][210];
int dp[210];

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int main() {
	freopen("1359.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	memset(dp, -1, sizeof(dp));
	dp[1] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			dp[j] = min(dp[j], dp[i] + arr[i][j]);
		}
	}
	printf("%d\n", dp[n]);
	return 0;
}
