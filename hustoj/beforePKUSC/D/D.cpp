#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
using namespace std;

struct edge
{
	int v, w, next; 
} e[10005];

struct query
{
	unsigned char u, s1, s2;
}q[3000005];

int n, m, k, cnt, T, ans, head[105], dp[51][256][256], 
    fast[105][105], a[105], b[105], bin[105];

bool vis[51][256][256];

void insert(int u, int v, int w) {
	e[cnt] = (edge) {v, w, head[u]}, head[u] = cnt++;
}

int main()
{
	freopen("sample.in", "r", stdin);

	scanf("%d", &T);

	while (T--) {
		scanf("%d%d%d", &n, &m, &k);	

		cnt = 0, ans = -1;

		memset(vis, 0, sizeof vis);
		memset(dp, -1, sizeof dp);
		memset(head, -1, sizeof head);
		memset(bin, 0, sizeof bin);
		memset(fast, 0, sizeof fast);		

		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			insert(u, v, w);
			insert(v, u, w);
		}
	
		for (int i = 0; i < k; i++) {
			int s; scanf("%d", &s);
			bin[s] = (1 << i);
			scanf("%d%d", &a[s], &b[s]);

			int t; scanf("%d", &t);
			for (int j = 1; j <= t; j++) {
				int v; scanf("%d", &v);
				fast[v][i] = 1;
			}
		}

		int lift = 0, right = 1;

		insert(0, 1, 0), dp[0][0][0] = 0;
		q[lift] = (query) {0, 0, 0};

		while (lift != right) {
			query th = q[lift++];
			if (lift == 3000000)
				lift = 0;

			int u = th.u, s1 = th.s1, s2 = th.s2;
			vis[u][s1][s2] = 0;

			for (int i = head[u]; i != -1; i = e[i].next) {
				int v = e[i].v, t1 = s1, t2 = (s2 | bin[v]);

				for (int j = 0; j < k; j++)
					t1 |= fast[v][j] * (1 << j);

				if (dp[v][t1][s2] == -1 || dp[v][t1][s2] > dp[u][s1][s2] + e[i].w) {
					dp[v][t1][s2] = dp[u][s1][s2] + e[i].w;
					if (!vis[v][t1][s2]) {
						vis[v][t1][s2] = 1;
						q[right++] = (query) {v, t1, s2};
						if (right == 3000000)
							right = 0;
					}
				}

				int tmp = dp[u][s1][s2] + e[i].w + ((bin[v] & t1) ? b[v] : a[v]);

				if (t2 != s2 && (dp[v][t1][t2] == -1 || dp[v][t1][t2] > tmp)) {
					dp[v][t1][t2] = tmp;
					if (!vis[v][t1][t2]) {
						vis[v][t1][t2] = 1;
						q[right++] = (query) {v, t1, t2};
						if (right == 3000000)
							right = 0;
					}
				}
			}
		}

		for (int i = 0; i < (1 << k); i++)
			if (dp[1][i][(1 << k) - 1] != -1 && (ans == -1 || ans > dp[1][i][(1 << k) - 1]))
				ans = dp[1][i][(1 << k) - 1];

		printf("%d\n", ans);
	}

	return 0;
}	
