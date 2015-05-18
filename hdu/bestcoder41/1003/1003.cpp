#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

const int MAXN = 100005;
const int MOD = 998244353;

int T;
int n, c, L, R;
map<int, int> dp[2];

int get(int a, int b) {
	int k = b - a + 1;
	int c = a + b;
	if (k & 1) c /= 2;
	else k /= 2;
	return c * k;
}

int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d", &n, &c, &L, &R);
		int idx = 0;
		dp[idx].clear();
		dp[idx][c] = 1;
		for (int i = 1; i <= min(n - 1, R); i++) {
			idx ^= 1;
			dp[idx].clear();
			bool flag = false;
			for (map<int, int>::iterator it = dp[idx ^ 1].begin(); it != dp[idx ^ 1].end(); it++) {
				int sum = it -> first;
				int value = it -> second;
				if (sum + i <= R) {
					dp[idx][sum + i] += value;
					dp[idx][sum + i] %= MOD;
					flag = true;
				}
				if (sum + get(i + 1, n - 1) >= L) {
					dp[idx][sum] += value;
					dp[idx][sum] %= MOD;
				}
			}
			if (!flag) {
				break;
			}
		}
		int ans = 0;
		for (int i = L; i <= R; i++) {
			ans += dp[idx][i];
			ans %= MOD;
		}
		printf("%d\n", ans);
	}

	return 0;
}
