#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 2600;
const int MAXM = 7000000;

int n, m, r, c;
char map[55][55];
struct Edge{ int to, next; } edges[MAXM];
int head[MAXN], cnt = 0;

void insert(int u, int v) {
	edges[cnt] = (Edge){v, head[u]}, head[u] = cnt++;
}

void check(int i, int j, int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= m) return;
	if (map[x][y] == 'x') return;
	insert(i * m + j, x * m + y);
}

bool vis[MAXN];
int mat[MAXN];
int dfs(int x) {
	for (int p = head[x]; p != -1; p = edges[p].next) {
		int v = edges[p].to;
		if (!vis[v]) {
			vis[v] = 1;
			if (mat[v] == -1 || dfs(mat[v])) {
				mat[v] = x;
				return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("2150.in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &r, &c);
	for (int i = 0; i < n; i++)
		scanf("%s", map[i]);
	memset(head, -1, sizeof(head));
	memset(mat, -1, sizeof(mat));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 'x') continue;
			check(i, j, i + r, j + c);
			check(i, j, i + r, j - c);
			check(i, j, i + c, j + r);
			check(i, j, i + c, j - r);
		}
	}
	int tot = 0, ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 'x') continue;
			int x = i * m + j;
			memset(vis, 0, sizeof(vis));
			ans += dfs(x);
			tot++;
		}
	}
	printf("%d\n", tot - ans);
	return 0;
}
