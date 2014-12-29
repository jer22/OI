#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m, p, s;
int v[111];
int w[111];
int dp[111][111];
int main() {
	freopen("2159.in", "r", stdin);
	while (~scanf("%d %d %d %d", &n, &m, &p, &s)) {
		for (int i = 1; i <= p; i++)
			scanf("%d %d", &v[i], &w[i]);
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= p; i++) {
			for (int j = w[i]; j <= m; j++) {
				for (int k = 1; k <= s; k++) {
					dp[j][k] = max(dp[j][k], dp[j - w[i]][k - 1] + v[i]);
				}
			}
		}
		bool flag = false;
		for (int j = 0; j <= m; j++) {
			for (int k = 1; k <= s; k++) {
				if (dp[j][k] >= n) {
					printf("%d\n", m - j);
					flag = true;
					break;
				}
			}
			if (flag) break;
		}
		if (!flag) printf("-1\n");
	}
	return 0;
}
