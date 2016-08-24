#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;

int n;
int dp[MAXN][105];
int p[MAXN][27];
char s[MAXN];
string ans;
int main() {
	freopen("b.in", "r", stdin);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 26; j++)
			p[i][j] = p[i - 1][j];
		p[i][s[i] - 'a'] = i;
	}
	for (int i = 1; i <= n; i++)
		dp[i][0] = i + 1, dp[i][1] = i;
	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= 100; j++) {
			dp[i][j] = dp[i - 1][j];
			if (dp[i - 1][j - 2])
				dp[i][j] = max(dp[i][j], p[dp[i - 1][j - 2] - 1][s[i] - 'a']);
		}
	}
	int len = 100;
	while (!dp[n][len]) len--;
	int t = n;
	while (len > 1) {
		ans.push_back(s[dp[t][len]]);
		t = p[t][s[dp[t][len]] - 'a'] - 1;
		len -= 2;
	}
	cout << ans;
	if (len) cout << s[dp[t][len]];
	reverse(ans.begin(), ans.end());
	cout << ans << endl;

	return 0;
}
