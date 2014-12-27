#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
double possible[10005];
int cost[10005];
double dp[10005];
int main() {
	while (~scanf("%d %d", &n, &m)) {
		if (!n && !m) break;
		memset(possible, 0, sizeof(possible));
		memset(cost, 0, sizeof(cost));
		for (int i = 1; i <= m; i++) {
			scanf("%d %lf", &cost[i], &possible[i]);
			possible[i] = 1.0 - possible[i];
		}
		for (int i = 0; i <= n; i++)
			dp[i] = 1;
		for (int i = 1; i <= m; i++) {
			for (int j = n; j >= cost[i]; j--) {
				dp[j] = min(dp[j], dp[j - cost[i]] * possible[i]);
			}
		}
		printf("%.1lf%%\n", (1 - dp[n]) * 100);
	}
	return 0;
}
