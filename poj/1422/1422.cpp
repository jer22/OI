#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int T;
int n, m;
vector<int> edges[125];
int vis[125];
int mat[125];
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
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	freopen("1422.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		int a, b;
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
		}
		memset(mat, 0, sizeof(mat));
		int ans = match();
		printf("%d\n", n - ans);
	}

	return 0;
}
