/*
ID:shijiey1
PROG:money
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int V, N;
int arr[30];
long long dp[10010];
int main() {
	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);
	scanf("%d %d", &V, &N);
	for (int i = 1; i <= V; i++) {
		scanf("%d", &arr[i]);
	}
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 1; i <= V; i++) {
		for (int j = arr[i]; j <= N; j++) {
			dp[j] += dp[j - arr[i]];
		}
	}
	printf("%lld\n", dp[N]);
	return 0;
}
