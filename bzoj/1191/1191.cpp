#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int mat[1005];
bool vis[1005];
vector<int> edges[1005];

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
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (!dfs(i)) return i - 1;
	}
	return n;
}

int main() {
	freopen("1191.in", "r", stdin);
	scanf("%d %d", &m, &n);
	int a, b;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a, &b);
		a++, b++;
		edges[i].push_back(a);
		edges[i].push_back(b);
	}
	int ans = match();
	cout << ans << endl;
	return 0;
}
