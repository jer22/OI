#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const long long MOD = 772002;

int n, m;
char arr[8][8];

int tot;
long long dp[30][2030];
int dir[9][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}, {0, 0}};
int id[8][8];

bool check(int i, int j) {
	if (i < 1) return false;
	if (i > n) return false;
	if (j < 1) return false;
	if (j > m) return false;
	return true;
}

long long ans;
int cnt[1 << 11];
bool unfilled[10][10];
long long calc() {
	pii stac[11];
	memset(dp, 0, sizeof(dp));
	memset(cnt, 0, sizeof(cnt));
	int top = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j] == 'X') stac[++top] = mp(i, j);
		}
	}
	for (int stat = 0; stat < 1 << top; stat++) {
		memset(unfilled, 0, sizeof(unfilled));
		for (int i = 1; i <= top; i++) {
			if (~stat & (1 << i - 1)) {
				unfilled[stac[i].first][stac[i].second] = true;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int k;
				for (k = 0; k < 9; k++) {
					if (!check(i + dir[k][0], j + dir[k][1])) continue;
					if (unfilled[i + dir[k][0]][j + dir[k][1]])
						break;
				}
				if (k == 9) {
					cnt[stat]++;
				}
			}
		}
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n * m; i++) {
		for (int stat = 0; stat < 1 << top; stat++) {
			(dp[i][stat] += dp[i - 1][stat] * (long long)max(cnt[stat] - i + 1, 0)) %= MOD;
			for (int j = 1; j <= top; j++) {
				if (stat & (1 << j - 1))
					(dp[i][stat] += dp[i - 1][stat ^ (1 << j - 1)]) %= MOD;
			}
		}
	}
	return dp[n * m][(1 << top) - 1] % MOD;
}

void dfs(int x, int y, int cnt) {
	if (y == m + 1) {
		dfs(x + 1, 1, cnt);
		return;
	}
	if (x == n + 1) {
		(ans += calc() * (cnt & 1 ? -1 : 1)) %= MOD;
		return;
	}
	dfs(x, y + 1, cnt);
	int k;
	for (k = 0; k < 9; k++) {
		if (!check(x + dir[k][0], y + dir[k][1])) continue;
		if (arr[x + dir[k][0]][y + dir[k][1]] == 'X') break;
	}
	if (k == 9) {
		arr[x][y] = 'X';
		dfs(x, y + 1, cnt + 1);
		arr[x][y] = '.';
	}
}

int main() {
	// freopen("1007.in", "r", stdin);
	int cas = 0;
	while (~scanf("%d %d", &n, &m)) {
		cas++;

		memset(arr, 0, sizeof(arr));
		tot = 0;
		memset(id, -1, sizeof(id));
		for (int i = 1; i <= n; i++) {
			scanf("%s", arr[i] + 1);
			for (int j = 1; j <= m; j++) {
				if (arr[i][j] == 'X') {
					id[i][j] = tot++;
				}
			}
		}

		if (n == 1 && m == 1) {
			if (arr[1][1] == 'X')
				printf("Case #%d: 1\n", cas);
			else printf("Case #%d: 0\n", cas);
			continue;
		}
		/************************************************/
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (arr[i][j] != 'X') continue;
				for (int k = 0; k < 8; k++) {
					int ni = i + dir[k][0];
					int nj = j + dir[k][1];
					if (!check(ni, nj)) continue;
					if (arr[ni][nj] == 'X') {
						flag = false;
						break;
					}
				}
				if (!flag) break;
			}
			if (!flag) break;
		}
		if (!flag) {
			// cout << 0 << endl;
			printf("Case #%d: 0\n", cas);
			continue;
		}
		/************************************************/
		
		ans = 0;
		dfs(1, 1, 0);
		// cout << (ans + MOD) % MOD << endl;
		printf("Case #%d: %lld\n", cas, (ans + MOD) % MOD);
	}



	return 0;
}
