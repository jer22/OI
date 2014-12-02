#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 10010

using namespace std;

struct Pipe{
	int p, l, h;
	bool operator < (const Pipe &pi) const {
		return p < pi.p;
	}
};

int n, m, k;
int up[MAXN];
int down[MAXN];
Pipe pipes[MAXN];
int dp[2][1010];

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int main() {
	freopen("1941.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &up[i], &down[i]);
	}
	for (int i = 0; i < k; i++) {
		scanf("%d %d %d", &pipes[i].p, &pipes[i].l, &pipes[i].h);
	}
	int cnt = 0;
	sort(pipes, pipes + k);
	dp[0][0] = dp[1][0] = -1;
	int i;
	int flag;
	bool fl = false;
	for (i = 1; i <= n; i++) {
		memset(dp[i % 2], -1, sizeof(dp[i % 2]));
		flag = 0;
		if (pipes[cnt].p == i) {
			flag = 1;
		}
		for (int j = 1; j <= m; j++) {
			if ((flag == 1 || flag == 2) && (j <= pipes[cnt].l || j >= pipes[cnt].h)) {
				dp[i % 2][j] = -1;
				continue;
			}
			if (j + down[i - 1] <= m && dp[1 - (i % 2)][j + down[i - 1]] != -1) {
				dp[i % 2][j] = min(dp[i % 2][j], dp[1 - (i % 2)][j + down[i - 1]]);
			}
			int k = j;
			int s = 1;
			while (k - up[i - 1] > 0) {
				if (dp[1 - (i % 2)][k - up[i - 1]] != -1) {
					dp[i % 2][j] = min(dp[i % 2][j], dp[1 - (i % 2)][k - up[i - 1]] + s);
				}
				k -= up[i - 1];
				s++;
			}
			if (j == m) {
				for (int k = m; k >= m - up[i - 1]; k--) {
					if (dp[1 - (i % 2)][k] != -1) {
						dp[i % 2][m] = min(dp[i % 2][m], dp[1 - (i % 2)][k] + 1);
					}
				}
			}
			if (dp[i % 2][j] != -1 && flag == 1) {
				flag = 2;
			}
		}
		if (flag == 2) {
			cnt++;
		}
		fl = false;
		for (int j = 1; j <= m; j++) {
			if (dp[i % 2][j] != -1) {
				fl = true;
			}
		}
		if (!fl) break;
	}
	if (i <= n) {
		printf("0\n%d\n", cnt);
		return 0;
	}
	int minnum = -1;
	for (int j = 1; j <= m; j++) {
		minnum = min(minnum, dp[n % 2][j]);
	}
	printf("1\n%d\n", minnum);
	return 0;
}
