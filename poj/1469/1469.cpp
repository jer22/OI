#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int T;
int n, m;
vector<int> edges[105];
int mat[305];
int vis[305];

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
	freopen("1469.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		int k, a;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d", &k);
			for (int j = 1; j <= k; j++) {
				scanf("%d", &a);
				edges[i].push_back(a);
			}
		}
		memset(mat, 0, sizeof(mat));
		int ans = match();
		if (ans == n) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
