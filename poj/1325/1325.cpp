#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
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
	int ans = 0;
	for (int i = 0; i < n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	freopen("1325.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		scanf("%d %d", &m, &k);
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		int a, b, c;
		for (int i = 0; i < k; i++) {
			scanf("%d %d %d", &a, &b, &c);
			if (!(b * c)) continue;
			edges[b].push_back(c);
		}
		int ans = match();
		cout << ans << endl;
	}
	return 0;
}
