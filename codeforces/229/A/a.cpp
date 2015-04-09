#include <bits/stdc++.h>

using namespace std;

int n, m;
string str[105];
int dp[105][10005];
bool vis[10005];
void bfs(int id) {
	string s = str[id];
	queue<int> q;
	memset(dp[id], 0x3f, sizeof(dp[id]));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < m; i++) {
		if (s[i] == '1') {
			dp[id][i] = 0;
			vis[i] = 1;
			q.push(i);
		}
	}
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		int nex = cur ? cur - 1 : m - 1;
		if (dp[id][cur] + 1 < dp[id][nex]) {
			dp[id][nex] = dp[id][cur] + 1;
			if (!vis[nex]) {
				vis[nex] = 1;
				q.push(nex);
			}
		}
		nex = (cur < m - 1) ? cur + 1 : 0;
		if (dp[id][cur] + 1 < dp[id][nex]) {
			dp[id][nex] = dp[id][cur] + 1;
			if (!vis[nex]) {
				vis[nex] = 1;
				q.push(nex);
			}
		}
		vis[cur] = 0;
	}

}

int main() {
	// freopen("a.in", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> str[i];
	for (int i = 0; i < n; i++)
		bfs(i);
	int ans = 0x3f3f3f3f;
	for (int j = 0; j < m; j++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (dp[i][j] == 0x3f3f3f3f) {
				cout << -1 << endl;
				return 0;
			}
			cnt += dp[i][j];
		}
		ans = min(ans, cnt);
	}

	if (ans == 0x3f3f3f3f) cout << -1 << endl;
	else cout << ans << endl;
	return 0;
}
