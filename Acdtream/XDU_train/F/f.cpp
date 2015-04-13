#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int T, n, m, K;
int arr[105][105];
vector<int> edges[105];
int mat[105];
bool vis[105];
void build(int x) {
	for (int i = 0; i <= n; i++)
		edges[i].clear();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j] > x) continue;
			edges[i].push_back(j);
		}
	}
}

bool dfs(int u) {
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!vis[v]) {
			vis[v] = 1;
			if (!mat[v] || dfs(mat[v])) {
				mat[v] = u;
				return true;
			}
		}
	}
	return false;
}

int match() {
	memset(mat, 0, sizeof(mat));
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int solve() {
	int l = 0, r = 1000000000;
	while (l < r) {
		int mid = l + r >> 1;
		build(mid);
		int x = match();
		if (x > n - K) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main() {
	freopen("f.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		cin >> n >> m >> K;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &arr[i][j]);
		int ans = solve();
		printf("Case #%d: %d\n", cas, ans);
	}


	return 0;
}
