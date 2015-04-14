#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MOD 100000000

using namespace std;

int n, m;
int ok[15];
int tot, stat[400];
int dp[15][5000];

bool fuck(int x) {
	for (int i = 0; i < m - 1; i++) {
		int a = (x >> i) & 1;
		int b = (x >> (i + 1)) & 1;
		if (a && b) return false;
	}
	return true;
}

bool check(int a, int b) {
	for (int i = 0; i < m; i++) {
		int x = (a >> i) & 1;
		int y = (b >> i) & 1;
		if (x && y) return false;
	}
	return true;
}

int main() {
	freopen("1725.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < 1 << m; i++)
		if (fuck(i)) stat[tot++] = i;
	int t;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &t);
			ok[i] |= (!t) << j;
		}
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 0; j < tot; j++) {
			int now = stat[j];
			if (now & ok[i]) continue;
			for (int k = 0; k < tot; k++) {
				int pre = stat[k];
				if (check(now, pre)) dp[i][now] += dp[i - 1][pre];
				dp[i][now] %= MOD;
			}
		}
	}
	cout << dp[n + 1][0] << endl;
	return 0;
}
