#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

int n, k, low;
int color[MAXN];
int cost[MAXN];
// arr[i][j]表示第0到第i个客栈中颜色为j的客栈的个数
int arr[MAXN][55];
int main( void ) {
	freopen("1311.in", "r", stdin);
	scanf("%d %d %d", &n, &k, &low);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &color[i], &cost[i]);
	}
	// 预处理arr[i][j]
	arr[0][color[0]] = 1;
	for (int i = 0; i < k; i++) {
		for (int j = 1; j < n; j++) {
			if (i == color[j]) {
				arr[j][i] = arr[j - 1][i] + 1;
			} else {
				arr[j][i] = arr[j - 1][i];
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int j = i;
		while (cost[j] > low) {
			j++;
		}
		if (j == i) {
			ans += arr[n - 1][color[i]] - arr[j][color[i]];
		} else {
			ans += arr[n - 1][color[i]] - arr[j - 1][color[i]];
		}
	}
	printf("%d\n", ans);
	return 0;
}
