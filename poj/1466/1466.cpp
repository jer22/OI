#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> edges[505];
int mat[505];
bool vis[505];

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
	freopen("1466.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a, b, k;
		char ch;
		for (int i = 0; i < n; i++)
			edges[i].clear();
		for (int i = 0; i < n; i++) {
			cin >> a >> ch >> ch >> k >> ch;
			for (int i = 0; i < k; i++) {
				scanf("%d", &b);
				edges[a].push_back(b);
			}
		}
		memset(mat, 0, sizeof(mat));
		int ans = n - match() / 2;
		printf("%d\n", ans);
	}


	return 0;
}
