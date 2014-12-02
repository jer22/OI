#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
long long dp[15][5000];

/*
all of the states of LINE i

@param i: current line
@param j: vertical (m - 1 to 0)
@param stat: next state
@param pre: line i's state
*/
void dfs(int i, int j, int stat, int pre) {
	// printf("%d %d %d %d\n", i, j, stat, pre);
	if (j == -1) {
		dp[i + 1][stat] += dp[i][pre];
		return;
	}

	if ((pre & (1 << j)) == (1 << j)) {
		dfs(i, j - 1, stat, pre);
	} else {
		dfs(i, j - 1, (stat | (1 << j)), pre);
	}

	if (j - 1 >= 0 && (!(pre & (1 << j))) && (!(pre & (1 << (j - 1))))) {
		dfs(i, j - 2, stat, pre);
	}

}

int main() {
	freopen("2411.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		if (!n && !m) break;
		memset(dp, 0, sizeof(dp));
		dp[1][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int pre = 0; pre < (1 << m); pre++) {
				if (dp[i][pre]) {
					// printf("%d %d\n", i, pre);
					dfs(i, m - 1, 0, pre);
				}
			}
		}
		// printf("%d %d\n", dp[2][0], dp[2][3]);
		printf("%lld\n", dp[n + 1][0]);
	}

	
	return 0;
}
