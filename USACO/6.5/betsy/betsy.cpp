/*
ID:shijiey1
LANG:C++
PROG:betsy
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int dp[9][1 << (9 << 1)];
int stat[500];
int brk[500][20], stack[20], top = 0, tot = 0;

int main() {
	freopen("betsy.in", "r", stdin);
	freopen("betsy.out", "w", stdout);
	scanf("%d", &n);
	if (n == 1) {
		cout << 1 << endl;
		return 0;
	}
	m = 1 << ((n + 1) << 1);
	for (int i = 0; i < m; i++) {
		top = 0;
		for (int j = 0; j <= n; j++) {
			int x = i >> (j << 1);
			if ((x & 3) == 1) stack[top++] = j;
			if ((x & 3) == 2)
				if (top--) {
					brk[tot][j] = stack[top];
					brk[tot][stack[top]] = j;
				} else break;
			if ((x & 3) == 3) {
				top = -1;
				break;
			}
		}
		if (!top) stat[tot++] = i;
	}
	int ans = 0;
	dp[n][1 | (2 << ((n - 1) << 1))] = 1;
	for (int k = 1; k <= n; k++) {
		for (int i = 0; i < tot; i++) {
			if (stat[i] & 3) dp[0][stat[i]] = 0;
			else dp[0][stat[i]] = dp[n][stat[i] >> 2]; 
		}
		for (int i = 1; i <= n; i++) {
			int x = (i - 1) << 1;
			memset(dp[i], 0, sizeof(dp[i]));
			for (int j = 0; j < tot; j++) {
				int p = (stat[j] >> x) & 3;
				int q = (stat[j] >> (x + 2)) & 3;
				if (!p && !q) dp[i][stat[j] | (9 << x)] += dp[i - 1][stat[j]];
				else if (p && q) {
					if (p == q) {
						if (p == 1) dp[i][stat[j] ^ (5 << x) ^ (3 << (brk[j][i] << 1))] += dp[i - 1][stat[j]];
						else dp[i][stat[j] ^ (10 << x) ^ (3 << (brk[j][i - 1] << 1))] += dp[i - 1][stat[j]];
					} else {
						if (p == 1) {
							if (k == n && i == n && stat[j] == (9 << x)) ans += dp[i - 1][stat[j]];;
						} else dp[i][stat[j] ^ (6 << x)] += dp[i - 1][stat[j]];
					}
				} else {
					dp[i][stat[j]] += dp[i - 1][stat[j]];
					dp[i][stat[j] ^ (p << x) ^ (q << x + 2) | (p << x + 2) | (q << x)] += dp[i - 1][stat[j]];
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
