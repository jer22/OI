#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int n;
int fa[MAXN];
bool vis[MAXN];
int lcm(int a, int b) {
	return a * b / __gcd(a, b);
}
int dfs(int x) {
	vis[x] = 1;
	if (vis[fa[x]]) return 1;
	return dfs(fa[x]) + 1;
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &n);
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &fa[i]);
		if (vis[fa[i]]) flag = false;
		vis[fa[i]] = 1;
	}
	if (!flag) cout << -1 << endl;
	else {
		memset(vis, 0, sizeof(vis));
		int ans = 1;
		vector<int> q;

		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				int t = dfs(i);
				if (!(t & 1)) t >>= 1;
				q.push_back(t);
			}
		}
		for (int i = 0; i < q.size(); i++) {
			ans = lcm(ans, (int)q[i]);
		}
		cout << ans << endl;
	}


	return 0;
}
