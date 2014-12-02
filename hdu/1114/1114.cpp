#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int dp[1000005];
int main() {
	freopen("1114.in", "r", stdin);
	int T;
	scanf("%d", &T);
	int w1, w2;
	int value[510];
	int weight[510];
	while (T--) {
		memset(value, 0, sizeof(value));
		memset(weight, 0, sizeof(weight));
		scanf("%d %d", &w1, &w2);
		int w = w2 - w1;
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &value[i], &weight[i]);
		}
		for (int i = 0; i <= w; i++) {
			dp[i] = INF;
		}
		dp[0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = weight[i]; j <= w; j++) {
				dp[j] = min(dp[j], dp[j - weight[i]] + value[i]);
			}
		}
		if (dp[w] == INF) printf("This is impossible.\n");
		else printf("The minimum amount of money in the piggy-bank is %d.\n", dp[w]);
	}

	return 0;
}
