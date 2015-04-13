#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MOD = 1e9 + 7;

int T, n, m;
long long contro[55];
long long dp[55][8];

int main() {
	freopen("f.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d %d", &n, &m);
		memset(contro, 0, sizeof(contro));
		for (int i = 0; i < m; i++) {
			int k;
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {
				int t;
				scanf("%d", &t);
				contro[i] |= (1ll << (long long)(t - 1));
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					memset(dp, 0, sizeof(dp));
					dp[0][0] = 1;
					for (int t = 0; t < m; t++) {
						int stat = 0;
						if ((contro[t] & (1ll << i))) stat |= 1;
						if ((contro[t] & (1ll << j))) stat |= 2;
						if ((contro[t] & (1ll << k))) stat |= 4;
						for (int now = 0; now < 8; now++) {
							dp[t + 1][now ^ stat] += dp[t][now];
							dp[t + 1][now ^ stat] %= MOD;
							dp[t + 1][now] += dp[t][now];
							dp[t + 1][now] %= MOD;
						}
					}
					ans += dp[m][7];
					ans %= MOD;
				}
			}
		}
		printf("Case #%d: %d\n",cas++,ans);
	}
	return 0;
}
