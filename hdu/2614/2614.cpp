#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[17][17];
int ans = 0;
int vis[17];
void dfs(int num, int pre, int step) {
	ans = max(ans, step);
	for (int i = 1; i < n; i++) {
		if (!vis[i] && arr[num][i] >= pre) {
			vis[i] = 1;
			dfs(i, arr[num][i], step + 1);
			vis[i] = 0;
		}
	}
}

int main() {
	while (~scanf("%d", &n)) {
		memset(arr, 0, sizeof(arr));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &arr[i][j]);
			}
		}
		ans = 0;
		dfs(0, 0, 1);
		printf("%d\n", ans);
	}
	return 0;
}
