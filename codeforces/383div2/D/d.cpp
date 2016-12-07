#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int n, m, w;
int fa[MAXN], wei[MAXN], bea[MAXN];
int vis[MAXN];
int findfa(int p) {
	if (p == fa[p]) return p;
	return fa[p] = findfa(fa[p]);
}
void un(int a, int b) {
	fa[findfa(a)] = findfa(b);
}

int ww[MAXN], bb[MAXN];
int dp[MAXN][MAXN];
vector<int> ss[MAXN];
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &w);
	for (int i = 1; i <= n; i++)
		scanf("%d", &wei[i]);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &bea[i]);
		fa[i] = i;
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		un(a, b);
	}
	int top = 0;
	for (int i = 1; i <= n; i++) {
		int t = findfa(i);
		if (!vis[t]) {
			top++;
			vis[t] = top;
		}
		ww[vis[t]] += wei[i];
		bb[vis[t]] += bea[i];
		ss[vis[t]].push_back(i);
	}
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 0; i < top; i++) {
		for (int j = 0; j <= w; j++) {
			if (dp[i][j] == -1) continue;
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
			if (j + ww[i + 1] <= w) dp[i + 1][j + ww[i + 1]] = max(dp[i + 1][j + ww[i + 1]], dp[i][j] + bb[i + 1]);
			for (int k = 0; k < ss[i + 1].size(); k++) {
				if (j + wei[ss[i + 1][k]] <= w) dp[i + 1][j + wei[ss[i + 1][k]]] = max(dp[i + 1][j + wei[ss[i + 1][k]]], dp[i][j] + bea[ss[i + 1][k]]);
			}
		}
	}
	int ans = 0;
	for (int i = w; i >= 0; i--)
		ans = max(ans, dp[top][i]);
	cout << ans << endl;

	return 0;
}
