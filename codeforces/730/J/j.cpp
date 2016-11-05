#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 105;

int n, sum = 0;
int rem[MAXN], cap[MAXN];
map<int, int> dp[MAXN][MAXN];

int getnbot() {
	int tmp[MAXN], tot = sum;
	for (int i = 1; i <= n; i++)
		tmp[i] = cap[i];
	sort(tmp + 1, tmp + n + 1);
	for (int i = n; i >= 1; i--) {
		if (tot <= tmp[i]) return n - i + 1;
		tot -= tmp[i];
	}
}

int main() {
	// freopen("j.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> rem[i];
		sum += rem[i];
	}
	for (int i = 1; i <= n; i++)
		cin >> cap[i];
	int nbot = getnbot();
	map<int, int>::iterator it;
	dp[0][0].insert(mp(0, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= nbot; j++) {
			for (it = dp[i][j].begin(); it != dp[i][j].end(); it++) {
				if (j < nbot) {
					int nk = it -> first + cap[i + 1] - rem[i + 1];
					if (dp[i + 1][j + 1].find(nk) == dp[i + 1][j + 1].end())
						dp[i + 1][j + 1].insert(mp(nk, it -> second));
					else dp[i + 1][j + 1][nk] = min(dp[i + 1][j + 1][nk], it -> second);
				}
				int nk = it -> first - rem[i + 1];
				int nw = it -> second + rem[i + 1];
				if (dp[i + 1][j].find(nk) == dp[i + 1][j].end())
					dp[i + 1][j].insert(mp(nk, nw));
				else dp[i + 1][j][nk] = min(dp[i + 1][j][nk], nw);
			}
		}
	}
	cout << nbot << ' ';
	int ans = 0x3f3f3f3f;
	for (it = dp[n][nbot].begin(); it != dp[n][nbot].end(); it++) {
		if (it -> first >= 0)
			ans = min(ans, it -> second);
	}
	cout << ans << endl;
	return 0;
}
