#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MOD = 20090717;

int n, m, k;
int nex[105][30], fail[105], ed[105];
int tot, root;

void insert(char *s, int id) {
	int len = strlen(s);
	int pos = root;
	for (int i = 0; i < len; i++) {
		int t = s[i] - 'a';
		if (!nex[pos][t]) nex[pos][t] = ++tot;
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
	freopen("2825.in", "r", stdin);
	for (int i = 0; i < 1 << 10; i++)
		for (int j = 0; j < 10; j++)
			num[i] += ((i >> j) & 1);
	while (~scanf("%d %d %d", &n, &m, &k)) {
		if (!n && !m && !k) break;
		memset(nex, 0, sizeof(nex));
		memset(ed, 0, sizeof(ed));
		char str[25];
		tot = root = 0;
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
					for (int t = 0; t < 26; t++) {
						int nj = nex[j][t];
						int np = (p | ed[nj]);
						dp[i + 1][nj][np] += dp[i][j][p];
						dp[i + 1][nj][np] %= MOD;
					}
				}
			}
		}
		int ans = 0;
		for (int j = 0; j <= tot; j++) {
			for (int p = 0; p < 1 << m; p++) {
				if (num[p] < k) continue;
				ans += dp[n][j][p];
				ans %= MOD;
			}
		}
		cout << ans << endl;
	}


	return 0;
}
