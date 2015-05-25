#include <bits/stdc++.h>

#define pii pair<int, int>

using namespace std;

struct Node{
	int value, weight, freq;
	bool operator < (const Node &n) const {
		return value < n.value;
	}
};

int n, K;
Node arr[75];
pii b[75];
int dp[75][75][75];
int main() {
	freopen("1564.in", "r", stdin);
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i].value);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i].weight);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i].freq);
	sort(arr + 1, arr + n + 1);
	for (int i = 1; i <= n; i++)
		b[i] = make_pair(arr[i].weight, i);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		arr[b[i].second].weight = i;
	for (int i = 1; i <= n; i++)
		arr[i].freq += arr[i - 1].freq;
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 1; i <= n + 1; i++)
		for (int k = 0; k <= n; k++)
			dp[i][i - 1][k] = 0;
	int ans = 0x3f3f3f3f;
	for (int w = n; w >= 0; w--) {
		for (int i = n; i >= 1; i--) {
			for (int j = i; j <= n; j++) {
				int t = arr[j].freq - arr[i - 1].freq;
				for (int k = i; k <= j; k++) {
					if (arr[k].weight >= w)
						dp[i][j][w] = min(dp[i][j][w], dp[i][k - 1][arr[k].weight] + dp[k + 1][j][arr[k].weight] + t);
					dp[i][j][w] = min(dp[i][j][w], dp[i][k - 1][w] + dp[k + 1][j][w] + K + t);
				}
			}
		}
		ans = min(ans, dp[1][n][w]);
	}
	printf("%d\n", ans);
	return 0;
}
