#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n;
int cnt[111];
int price[111];
int dp[111];
int main() {
	freopen("1300.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> cnt[i] >> price[i];
			cnt[i] += cnt[i - 1];
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			dp[i] = 0x3f3f3f3f;
			for (int j = 0; j < i; j++) {
				dp[i] = min(dp[i], dp[j] + (cnt[i] - cnt[j] + 10) * price[i]);
			}
		}
		cout << dp[n] << endl;
	}


	return 0;
}
