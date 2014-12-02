#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Rubbish{
	int tim, pow, hei;
	bool operator < (const Rubbish &r) const {
		return tim < r.tim;
	}
};

int h, n;
Rubbish arr[110];
int dp[110][3500];
int main() {
	freopen("1156.in", "r", stdin);
	scanf("%d %d", &h, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &arr[i].tim, &arr[i].pow, &arr[i].hei);
	}
	sort(arr + 1, arr + n + 1);
	arr[0].tim = arr[0].pow = arr[0].hei = 0;
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 10;
	int ans = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= h; j++) {
			if (dp[i][j] - arr[i + 1].tim >= 0) {
				// eat
				dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + arr[i + 1].pow);

				// heap
				dp[i + 1][min(h, j + arr[i + 1].hei)] = max(dp[i + 1][min(h, j + arr[i + 1].hei)], dp[i][j]);

			}
			if (dp[i + 1][h] - arr[i + 1].tim >= 0) {
				printf("%d\n", arr[i + 1].tim);
				return 0;
			}
		}
	}
	// while(1);
	for (int i = 1; i <= n; i++) {
		if (ans - arr[i].tim < 0) break;
			ans += arr[i].pow;
	}
	printf("%d\n", ans);
	return 0;
}
