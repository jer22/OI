#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define MAXN 110

using namespace std;

int n, m;
int arr[MAXN][MAXN];
int step[MAXN][MAXN];

int dfs(int i, int j) {
	if (step[i][j]) {
		return step[i][j];
	}
	int ans = 1;
	if (i > 1 && arr[i - 1][j] < arr[i][j]) {
		ans = max(dfs(i - 1, j) + 1, ans);
	}
	if (i < n && arr[i + 1][j] < arr[i][j]) {
		ans = max(dfs(i + 1, j) + 1, ans);
	}
	if (j > 1 && arr[i][j - 1] < arr[i][j]) {
		ans = max(dfs(i, j - 1) + 1, ans);
	}
	if (j < m && arr[i][j + 1] < arr[i][j]) {
		ans = max(dfs(i, j + 1) + 1, ans);
	}
	step[i][j] = ans;
	return ans;
}

int main() {
	freopen("1434.in", "r", stdin);
	memset(step, 0, sizeof(step));
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	int maxStep = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j] >= arr[i - 1][j] && arr[i][j] >= arr[i + 1][j]
				&& arr[i][j] >= arr[i][j - 1] && arr[i][j] >= arr[i][j + 1]) {
				maxStep = max(maxStep, dfs(i, j));
			}
		}
	}
	printf("%d\n", maxStep);

	return 0;
}
