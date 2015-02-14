#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int a[105], b[105];
vector<int> edges[105];
int mat[105], vis[105];

bool dfs(int k) {
	for (int i = 0; i < edges[k].size(); i++) {
		int j = edges[k][i];
		if (!vis[j]) {
			vis[j] = 1;
			if (!mat[j] || dfs(mat[j])) {
				mat[j] = k;
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

int main() {
	freopen("f.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			scanf("%d", &a[i]);
		}
		cin >> m;
		for (int i = 1; i <= m; i++)
			cin >> b[i];
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (abs(a[i] - b[j]) <= 1) edges[i].push_back(j);
			}
		}
		int ans = match();
		cout << ans << endl;
	}

	return 0;
}
