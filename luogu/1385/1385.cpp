#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int T;
string str;
long long dp[110][510];
int main() {
	freopen("1385.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		cin >> str;
		memset(dp, 0, sizeof(dp));
		int n = str.size();
		dp[0][str[0] - 'a' + 255] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 50; j <= 460; j++) {
				
				for (int k = a; k <= b; k++) {
					dp[i][j] += dp[i - 1][k];
					dp[i][j] %= 1000000007;
				}
			}
		}
		long long ans = 0;
		for (int i = 0; i < 26; i++) {
			printf("%lld %lld\n", i, dp[2][i]);
			ans += dp[n - 1][i];
			ans %= 1000000007;
		}
		printf("%lld\n", (ans - 1 + 1000000007) % 1000000007);
	}

	return 0;
}
