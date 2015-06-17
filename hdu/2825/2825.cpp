#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MOD = 20090717;

int n, m, k, tot, root;
int nex[105][26], fail[105], ed[105];

void insert(char str[], int id) {
	int len = strlen(str);
	int pos = root;
	for (int i = 0; i < len; i++) {
		int t = str[i] - 'a';
		if (!nex[pos][t])
			nex[pos][t] = ++tot;
		pos = nex[pos][t];
	}
	ed[pos] |= (1 << id);
}

void build() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		ed[p] |= ed[fail[p]];
		int t;
		for (int i = 0; i < 26; i++) {
			if (!(t = nex[p][i]))
				nex[p][i] = nex[fail[p]][i];
			else {
				fail[t] = p ? nex[fail[p]][i] : 0;
				q.push(t);
			}
		}
	}
}

int num[5030];
int dp[30][105][1 << 10];
int main() {
	for (int i = 0; i < 1 << 10; i++)
		for (int j = 0; j < 10; j++)
			num[i] += ((i >> j) & 1);
	while (~scanf("%d %d %d", &n, & m, &k)) {
		if (!n && !m && !k) break;
		char str[25];
		tot = root = 0;
		memset(ed, 0, sizeof(ed));
		memset(nex, 0, sizeof(nex));
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			insert(str, i);
		}
		build();
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= tot; j++) {
				for (int p = 0; p < 1 << m; p++) {
					if (!dp[i][j][p]) continue;
					for (int id = 0; id < 26; id++) {
						int nj = (p | ed[nex[j][id]]);
						dp[i + 1][nex[j][id]][nj] += dp[i][j][p];
						dp[i + 1][nex[j][id]][nj] %= MOD;
					}
				}
			}
		}
		int ans = 0;
		for (int p = 0; p < 1 << m; p++) {
			if (num[p] < k) continue;
			for (int i = 0; i <= tot; i++) {
				ans += dp[n][i][p];
				ans %= MOD;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
