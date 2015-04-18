#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int n;
int arr[55];
long long end = (1 << 20) - 1;
long long c[55][55];
bool vis[55];
long long dp[2][2000005];

int main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		end &= arr[i];
	}
	int now = 1, nex = 0;
	dp[0][(1 << 20) - 1] = 1;
	for (int i = 0; i < n; i++) {
		now ^= 1;
		nex ^= 1;
		memset(dp[nex], 0, sizeof(dp[nex]));
		for (int j = 0; j < 1 << 20; j++) {
			if (!dp[now][j]) continue;
			dp[nex][j & arr[i + 1]] += dp[now][j];
			dp[nex][j] += dp[now][j];
		}
	}
	long long ans = 0;
	for (int i = 1; i < (1 << 20) - 1; i++) {
		if (dp[nex][i] && (i ^ end)) {
			// cout << i << ' ' << dp[nex][i] << endl;
			ans += dp[nex][i];
		}

	}
	cout << (1 << n) - 2 - ans * 2 << endl;

	return 0;
}
