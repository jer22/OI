#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const long long MOD = 1000000007;

int n, m;
char str[2005][2005];
long long dp1[2005][2005], dp2[2005][2005];

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", str[i] + 1);
	dp1[1][2] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 2; j <= m; j++) {
			if (str[i][j] == '1' || (i == 1 && j == 2)) continue;
			dp1[i][j] += dp1[i - 1][j];
			dp1[i][j] %= MOD;
			dp1[i][j] += dp1[i][j - 1];
			dp1[i][j] %= MOD;
		}
	}
	dp2[2][1] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str[i][j] == '1' || (i == 2 && j == 1)) continue;
			dp2[i][j] += dp2[i - 1][j];
			dp2[i][j] %= MOD;
			dp2[i][j] += dp2[i][j - 1];
			dp2[i][j] %= MOD;
		}
	}
	long long t = dp1[n - 1][m] * dp2[n][m - 1] - dp1[n][m - 1] * dp2[n - 1][m];
	while (t < 0) t += MOD;
	cout << t % MOD << endl;

	return 0;
}
