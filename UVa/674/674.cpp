#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
long long dp[8050];
int arr[5] = {1, 5, 10, 25, 50};
int main() {
	freopen("674.in", "r", stdin);
	while (~scanf("%d", &n)) {
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		
		for (int j = 0; j < 5; j++) {
			for (int i = arr[j]; i <= n; i++) {
				dp[i] += dp[i - arr[j]];
			}
		}
		printf("%lld\n", dp[n]);
	}

	return 0;
}
