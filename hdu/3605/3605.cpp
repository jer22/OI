#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
bool edges[100005][15];
int cap[15];
int mat[15][100005];
int tot[15];
bool vis[15];

int read() {
	char ch;
	int a = 0;
	while((ch = getchar()) == ' ' || ch == '\n');
	a += ch - '0';
	while((ch = getchar()) != ' ' && ch != '\n') {
		a *= 10;
		a += ch - '0';
	}
	return a;
}

bool dfs(int u) {
	for (int i = 1; i <= m; i++) {
		if (edges[u][i] && !vis[i]) {
			vis[i] = 1;
			if (tot[i] < cap[i]) {
				mat[i][tot[i]++] = u;
				return true;
			}
			for (int j = 0; j < tot[i]; j++) {
				if (dfs(mat[i][j])) {
					mat[i][j] = u;
					return true;
				}
			}
		}
	}
	return false;
}

bool match() {
	memset(mat, 0, sizeof(mat));
	memset(tot, 0, sizeof(tot));
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (!dfs(i)) return false;
	}
	return true;
}

int main() {
	freopen("3605.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				edges[i][j] = read();
		for (int i = 1; i <= m; i++)
			scanf("%d", &cap[i]);		
		if (match()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
