#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

const int MOD = 20090717;

int n, m, k, tot, root;
int nex[1005][4], fail[1005], ed[1005], val[1005];

int getIdx(char c) {
	if (c == 'A') return 0;
	if (c == 'C') return 1;
	if (c == 'G') return 2;
	if (c == 'T') return 3;
}

void insert(char str[], int id) {
	int len = strlen(str);
	int pos = root;
	for (int i = 0; i < len; i++) {
		int t = getIdx(str[i]);
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
		for (int i = 0; i < 4; i++) {
			if (!(t = nex[p][i]))
				nex[p][i] = nex[fail[p]][i];
			else {
				fail[t] = p ? nex[fail[p]][i] : 0;
				q.push(t);
			}
		}
	}
}

int get(int stat){
	int ans = 0;
	for(int i = 0; i < m; i++)
		if(stat & (1 << i))
			ans += val[i];
	return ans;
}

int num[5030];
int dp[2][1005][1050];
int main() {
	freopen("n.in", "r", stdin);
	for (int i = 0; i < 1 << 10; i++)
		for (int j = 0; j < 10; j++)
			num[i] += ((i >> j) & 1);
	while (~scanf("%d %d", &m, &n)) {
		char str[105];
		tot = root = 0;
		memset(ed, 0, sizeof(ed));
		memset(nex, 0, sizeof(nex));
		memset(val, 0, sizeof(val));
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			scanf("%d", &val[i]);
			insert(str, i);
		}
		build();
		// for (int i = 0; i < 2; i++)
		// 	for (int j = 0; j <= tot; j++)
		// 		for (int k = 0; k < 1 << m; k++)
		// 			dp[i][j][k] = -INF;
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = 1;
		for (int i = 0; i < n; i++) {
			memset(dp[(i + 1) & 1], 0, sizeof(dp[(i + 1) & 1]));
			for (int j = 0; j <= tot; j++) {
				for (int p = 0; p < 1 << m; p++) {
					if (!dp[i & 1][j][p]) continue;
					for (int id = 0; id < 4; id++) {
						int nj = (p | ed[nex[j][id]]);
						dp[(i + 1) & 1][nex[j][id]][nj] = 1;
						// dp[i + 1][nex[j][id]][nj] %= MOD;
					}
				}
			}
		}
		int ans = -INF;
		for (int p = 0; p < 1 << m; p++) {
			for (int i = 0; i <= tot; i++) {
				if (dp[n & 1][i][p]) {
					// cout << p << endl;
					ans = max(ans, get(p));
					break;
				}
				// ans %= MOD;
			}
		}
		if (ans < 0) printf("No Rabbit after 2012!\n");
		else printf("%d\n", ans);
	}
	return 0;
}
