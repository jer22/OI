#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
const int MAXM = 100005;

int n, m;
int arr[MAXN], sum[MAXN];
int dp[2][10005], ans[MAXN][10005];

int main() {
	// freopen("f.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		sum[i] = arr[i] + sum[i - 1];
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		memset(dp[(i + 1) & 1], 0x3f, sizeof(dp[(i + 1) & 1]));
		for (int j = 0; j < MAXM / 10; j++) {
			if (dp[i & 1][j] == 0x3f3f3f3f) continue;
			int left = m + j - (sum[i] - dp[i & 1][j]);
			for (int k = 0; k <= left && k <= arr[i + 1] / 2; k++) {
				int nj = j + (arr[i + 1] - k) / 10;
				if (dp[i & 1][j] + arr[i + 1] - k < dp[(i + 1) & 1][nj]) {
					dp[(i + 1) & 1][nj] = dp[i & 1][j] + arr[i + 1] - k;
					ans[i + 1][nj] = k;
				}
			}
		}
	}
	int best = 0x3f3f3f3f;
	int idx;
	for (int i = 0; i < MAXM / 10; i++) {
		if (dp[n & 1][i] < best) {
			best = dp[n & 1][i];
			idx = i;
		}
	}
	stack<int> s;
	cout << best << endl;
	for (int i = n; i >= 1; i--) {
		s.push(ans[i][idx]);
		idx = idx - (arr[i] - ans[i][idx]) / 10;
	}
	while (!s.empty()) {
		cout << s.top() << " \n"[s.size() == 1];
		s.pop();
	}
	return 0;
}
