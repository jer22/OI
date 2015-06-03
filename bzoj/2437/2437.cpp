#include <bits/stdc++.h>

using namespace std;

int n, m;
int arr[45][45];
int tot;
int x, y;
int num[45][45];
vector<int> edges[10005];
bool vis[10005], ban[10005];
int mat[10050];

bool dfs(int i) {
	if (ban[i]) return false;
	for (int j = 0; j < edges[i].size(); j++) {
		int k = edges[i][j];
		if (!vis[k] && !ban[k]) {
			vis[k] = 1;
			if (!mat[k] || dfs(mat[k])) {
				mat[k] = i;
				mat[i] = k;
				return true;
			}
		}
	}
	return false;
}

int ans[10005];
int main() {
	scanf("%d %d", &n, &m);
	char str[45];
	for (int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		for (int j = 1; j <= m; j++) {
			if (str[j] == 'O') arr[i][j] = 1;
			else if (str[j] == 'X') arr[i][j] = 2;
			else arr[i][j] = 2, x = i, y = j;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (arr[i][j] == 1 ^ (((i + j) & 1) == ((x + y) & 1)))
				num[i][j] = ++tot;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!num[i][j]) continue;
			if (num[i + 1][j]) {
				edges[num[i][j]].push_back(num[i + 1][j]);
				edges[num[i + 1][j]].push_back(num[i][j]);
			}
			if (num[i][j + 1]) {
				edges[num[i][j]].push_back(num[i][j + 1]);
				edges[num[i][j + 1]].push_back(num[i][j]);
			}
		}
	}
	for (int i = 1; i <= tot; i++) {
		memset(vis, 0, sizeof(vis));
		if (!mat[i]) dfs(i);
	}
	int k;
	scanf("%d", &k);
	for (int i = 1; i <= k << 1; i++) {
		int fuck = num[x][y];
		ban[fuck] = 1;
		if (mat[fuck]) {
			int match = mat[fuck];
			mat[match] = mat[fuck] = 0;
			memset(vis, 0, sizeof(vis));
			ans[i] = (!dfs(match));
		}
		scanf("%d %d", &x, &y);
	}
	int res = 0;
	for (int i = 1; i <= k; i++)
		res += (ans[i * 2 - 1] & ans[i * 2]);
	printf("%d\n", res);
	for (int i = 1; i <= k; i++) {
		if (ans[i * 2 - 1] & ans[i * 2]) {
			printf("%d\n", i);
		}
	}
	return 0;
}
