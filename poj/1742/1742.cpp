#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int val[105];
int cnt[105];
bool dp[100005];
int num[100005];
int main() {
	freopen("1742.in", "r", stdin);
	while (~scanf("%d %d", &n, &m) && n && m) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &val[i]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &cnt[i]);
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			memset(num, 0, sizeof(num));
			for (int j = val[i]; j <= m; j++) {
				if (!dp[j] && dp[j - val[i]] && num[j - val[i]] < cnt[i]) {
					ans++;
					num[j] = num[j - val[i]] + 1;
					dp[j] = 1;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
