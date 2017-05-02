#include <bits/stdc++.h>

using namespace std;

struct Node{
	double rad, hei;
	Node() {}
	Node(double a, double b) : rad(a), hei(b) {}
	bool operator < (const Node &n) const {
		if (rad != n.rad) return rad < n.rad;
		return hei > n.hei;
	}
};

int T, n, k;
Node arr[1005];
double dp[1005][1005];
Node tmp[1005];
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &T);
	double pi = acos(-1);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf", &arr[i].rad, &arr[i].hei);
		}
		sort(arr + 1, arr + n + 1);
		double ans = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i <= n; i++) {
			for (int j = 1; j <= min(k - 1, i); j++) {
				for (int k = 0; k < i; k++) {
					dp[i][j] = max(dp[i][j], dp[k][j - 1] + 2 * pi * arr[i].rad * arr[i].hei);
				}
			}
			if (i >= k - 1) {
				for (int j = i + 1; j <= n; j++)
					ans = max(ans, dp[i][k - 1] + 2 * pi * arr[j].rad * arr[j].hei + pi * arr[j].rad * arr[j].rad);
			}
		}
		printf("Case #%d: %.10lf\n", cas, ans);
	}


	return 0;
}
