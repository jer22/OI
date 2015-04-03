#include <bits/stdc++.h>

using namespace std;

const int MAXN = 305;

int n;
int val[MAXN], cost[MAXN];
map<int, int> dp[MAXN];

int gcd(int a, int b) {
	if (a > b) swap(a, b);
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int main() {
	// freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> val[i];
	for (int i = 1; i <= n; i++)
		cin >> cost[i];
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (map<int, int>::iterator it = dp[i].begin(); it != dp[i].end(); it++) {
			int num = it -> first;
			int score = it -> second;
			if (dp[i + 1].find(num) == dp[i + 1].end()) {
				dp[i + 1][num] = score;
			} else dp[i + 1][num] = min(dp[i + 1][num], score);
			int nex = gcd(num, val[i + 1]);
			if (dp[i + 1].find(nex) == dp[i + 1].end()) {
				dp[i + 1][nex] = score + cost[i + 1];
			} else dp[i + 1][nex] = min(dp[i + 1][nex], score + cost[i + 1]);
		}
	}
	if (dp[n].find(1) == dp[n].end()) cout << -1 << endl;
	else cout << dp[n][1] << endl;

	return 0;
}
