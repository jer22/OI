#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int val[30];
long long dp[10005];
int main() {
	freopen("1708.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]);
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = val[i]; j <= m; j++) {
			dp[j] += dp[j - val[i]];
		}
	}
	cout << dp[m] << endl;


	return 0;
}
