#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 10005;

int n;
vector<int> edges[MAXN];
int mat[MAXN], vis[MAXN], res[MAXN];

bool dfs(int u) {
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!vis[v]) {
			vis[v] = 1;
			if (mat[v] == -1 || dfs(mat[v])) {
				mat[v] = u;
				return true;
			}
		}
	}
	return false;
}

int match() {
	int ans = 0;
	memset(mat, -1, sizeof(mat));
	for (int i = n - 1; i >= 0; i--) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	freopen("1562.in", "r", stdin);
	scanf("%d", &n);
	int t, a, b;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		a = (t + i) % n, b = i - t;
		if (b < 0) b += n;

		// cout << i << ' ' << a << ' ' << b << ' ' <<  endl;
		if (a > b) swap(a, b);
		edges[i].push_back(a);
		edges[i].push_back(b);
	}
	int ans = match();
	if (ans != n) {
		printf("No Answer\n");
		return 0;
	}
	for (int i = 0; i < n; i++)
		res[mat[i]] = i;
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", res[i]);
	}
	printf("\n");
	return 0;
}
