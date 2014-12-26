#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXS 42000

using namespace std;

int n, m;
int ex, ey;
int map[13][13];
int tot[2];
int size = 0, idx = 0;
int head[MAXS], next[MAXS], hash[MAXS];
long long stat[2][MAXS];
long long dp[2][MAXS];
int main() {
	freopen("1519.in", "r", stdin);
	// freopen("1519.out", "w", stdout);
	cin >> n >> m;
	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			cin >> c;
			if (c == '.') {
				map[i][j] = 1;
				ex = i, ey = j;
			}
		}
	}
	memset(map, 0, sizeof(map));
	total[idx] = 1;
	stat[idx][1] = 0;
	int ans = 0;
	dp[idx][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int k = 1; k <= tot[idx]; k++) stat[idx][k] <<= 2;
		for (int j = 1; j <= m; j++) {
			memset(head, -1, sizeof(head));
			size = 0;
			idx ^= 1;
			tot[idx] = 0;
			int x = (j - 1) << 1;
			for (int k = 1; k <= tot[idx ^ 1]; k++) {
				long long s = stat[idx ^ 1][k];
				long long cur = dp[idx ^ 1][k];
				int p = (s >> x) & 3;
				int q = (s >> (x + 2)) & 3;
				if (!map[i][j]) {
					if (!p && !q) insert(s, num);
				} else {
					if (!p && !q && map[i + 1][j] && map[i][j + 1])
						insert(s ^ (9 << x), num);
					else if (p && q) {
						if (p == q) {
							if (p == 1)
							else
						} else {
							if (p == 1)
							else
						}
					} else {

					}
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
