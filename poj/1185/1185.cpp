#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[110][15];
int dp[3][1055][1055];

void dfs(int i, int j, int stat, int pre1, int pre2, int cnt) {
	if (j < 0) {
		dp[(i + 1) % 3][stat][pre1] = max(dp[(i + 1) % 3][stat][pre1], dp[i % 3][pre1][pre2] + cnt);
		return;
	}

	dfs(i, j - 1, stat, pre1, pre2, cnt);
	if (!arr[i][m - j - 1] && !(pre1 & (1 << j))) {
		if (!(pre2 & (1 << j))) {
			dfs(i, j - 3, stat | (1 << j), pre1, pre2, cnt + 1);
		}
	}
}

int table[1100][1100];
void init() {
	for (int i = 0; i < 1 << m; i++) {
		for (int j = 0; j < 1 << m; j++) {
			if (!(i & j)) {
				table[i][++table[i][0]] = j;
			}
		}
	}
}

int main() {
	freopen("1185.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%c", &c);
			if (c == 'H') arr[i][j] = 1;
		}
		getchar();
	}
	memset(dp, -1, sizeof(dp));
	dp[1][0][0] = 0;
	init();
	for (int i = 1; i <= n; i++) {
		int pre2 = 0;
		memset(dp[(i + 1) % 3], -1, sizeof(dp[(i + 1) % 3]));
		for (int pre1 = 0; pre1 < 1 << m; pre1++) {
			for (int j = 1; j <= table[pre1][0]; j++) {
				pre2 = table[pre1][j];
				if (dp[i % 3][pre1][pre2] != -1) dfs(i, m - 1, 0, pre1, pre2, 0);
			}
		}
	}
	int ans = -1;
	for (int pre1 = 0; pre1 < 1 << m; pre1++) {
		for (int pre2 = 0; pre2 < 1 << m; pre2++) {
			if (dp[(n + 1) % 3][pre1][pre2] != -1) {
				ans = max(ans, dp[(n + 1) % 3][pre1][pre2]);
			}
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
