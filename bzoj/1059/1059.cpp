#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 205;

int T, n;
vector<int> edges[MAXN];
int mat[MAXN];
bool vis[MAXN];

bool dfs(int u) {
	for (int i = 0; i < edges[u].size(); i++) {
		int j = edges[u][i];
		if (!vis[j]) {
			vis[j] = 1;
			if (!mat[j] || dfs(mat[j])) {
				mat[j] = u;
				return true;
			}
		}
	}
	return false;
}

int match() {
	int ans = 0;
	memset(mat, 0, sizeof(mat));
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	freopen("1059.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int t;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &t);
				if (t) edges[i].push_back(j);
			}
		}
		if (n == match()) printf("Yes\n");
		else printf("No\n");
	}


	return 0;
}
