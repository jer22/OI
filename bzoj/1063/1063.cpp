#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int n, m;
long long p;
vector<int> edges[MAXN];
long long dp[MAXN][11][3];

long long get(long long x) {
	if (x && !(x % p)) return p;
	return x % p;
}

void dfs(int x, int pre) {
	for (int i = 0; i <= 10; i++)
		dp[x][i][0] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x);
		for (int j = 0; j <= 10; j++) {
			long long f1 = 0, f2 = 0;
			f1 = dp[nex][j][0] + dp[nex][j][1];
			if (j) f2 = dp[nex][j - 1][0] + dp[nex][j - 1][1] + dp[nex][j - 1][2];
			dp[x][j][2] = get(dp[x][j][2] * f2 + f1 * dp[x][j][1]);
			dp[x][j][1] = get(dp[x][j][1] * f2 + dp[x][j][0] * f1);
			dp[x][j][0] = get(dp[x][j][0] * f2);
		}
	}
}

int main() {
	freopen("1063.in", "r", stdin);
	scanf("%d %d %lld", &n, &m, &p);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	if (m != n - 1) {
		printf("-1\n-1\n");
		return 0;
	}
	dfs(1, 1);
	for (int i = 0; i <= 10; i++) {
		if (dp[1][i][0] + dp[1][i][1] + dp[1][i][2]) {
			printf("%d\n", i);
			printf("%lld\n", (dp[1][i][0] + dp[1][i][1] + dp[1][i][2]) % p);
			return 0;
		}
	}
	printf("-1\n-1\n");
	return 0;
}
