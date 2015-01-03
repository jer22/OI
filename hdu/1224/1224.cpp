#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n, m;
int point[111];
int arr[111][111];
int dp[111];
int pre[111];

void print(int x) {
	if (x == -1) return;
	print(pre[x]);
	printf("%d->", x);
}

int main() {
	freopen("1224.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &point[i]);
		scanf("%d", &m);
		memset(arr, 0, sizeof(arr));
		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			arr[a][b] = 1;
		}
		memset(dp, -1, sizeof(dp));
		memset(pre, -1, sizeof(pre));
		dp[1] = 0;
		point[n + 1] = 0;
		for (int i = 1; i <= n; i++) {
			if (dp[i] == -1) continue;
			for (int j = i + 1; j <= n + 1; j++) {
				if (!arr[i][j]) continue;
				if (dp[j] < dp[i] + point[j]) {
					dp[j] = dp[i] + point[j];
					pre[j] = i;
				}
			}
		}
		printf("CASE %d#\n", cas++);
		printf("points : %d\ncircuit : ", dp[n + 1]);
		print(pre[n + 1]);
		printf("1\n");
		if (T) cout << endl;
	}


	return 0;
}
