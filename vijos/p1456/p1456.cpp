#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 20
#define INF 0x3f3f3f3f

using namespace std;

int n;
int edges[MAXN][MAXN];
int dp[65546][MAXN];

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int main() {
	freopen("p1456.in", "r", stdin);
	scanf("%d", &n);
	int t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &edges[i][j]);
		}
	}
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; i++) {
		dp[1 << i][i] = 0;
	}
	int ans = -1;
	for (int i = 0; i < 1 << n; i++) {
		for (int j = 0; j < n; j++) {
			if (dp[i][j] != -1) {
				for (int k = 0; k < n; k++) {
					if (!(i & (1 << k))) {
						dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + edges[j][k]);
						if ((i | (1 << k)) == (1 << n) - 1) ans = min(ans, dp[i | (1 << k)][k]);
					}
				}
			}
		}
	}
	if (ans != -1)
		printf("%d\n", ans);
	else printf("0\n");

	return 0;
}

19.2 + 6.4

16 