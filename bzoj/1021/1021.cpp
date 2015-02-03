#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f
#define MAXM 1000
#define update(a,b) ((a)=(a)<(b)?(a):(b))
using namespace std;

int sum = 0;
int x1, x2, x3;
int sa, sb, sc;
int ea, eb, ec;
int a[7], b[7], c[7];
int money[6] = {1, 5, 10, 20, 50, 100};
int gcd[6] = {1, 5, 10, 10, 50, 100};
int now = 0;
int dp[2][3002][3002];
int solve() {
	if (ea < 0 || eb < 0 || ec < 0) return -1;
	for(int j = 0; j <= MAXM; j++)
            for(int k = 0; k <= MAXM; k++)
                dp[now][j][k] = INF;
	dp[now][sa][sb] = 0;
	for (int i = 0; i < 6; i++) {
		for(int j = 0; j <= MAXM; j++)
            for(int k = 0; k <= MAXM; k++)
                dp[now ^ 1][j][k] = dp[now][j][k];
		int t = gcd[i];
		int x, y;
		for (x = 0; (ea - x) % t; x++);
		for (y = 0; (eb - y) % t; y++);
		if ((ec - (sum - x - y)) % t) continue;
		for (int j = x; j <= MAXM; j += t) {
			if (sum - j - y < 0) break;
			for (int k = y; k <= MAXM; k += t) {
				int vc = sum - j - k;
				if (vc < 0) break;
				if (dp[now][j][k] == INF) continue;
				for (int r = 0; r <= a[i]; r++) {
					int p = j - r * money[i];
					if (p < 0) break;
					for (int l = 0; l <= r; l++) {
						int q = k + l * money[i];
						if (q > MAXM || vc + (r - l) * money[i] > MAXM) continue;
						dp[now ^ 1][p][q] = min(dp[now ^ 1][p][q], dp[now][j][k] + r);
					}
				}
				for (int r = 0; r <= b[i]; r++) {
					int p = k - r * money[i];
					if (p < 0) break;
					for (int l = 0; l <= r; l++) {
						int q = j + l * money[i];
						if (q > MAXM || vc + (r - l) * money[i] > MAXM) continue;
						dp[now ^ 1][q][p] = min(dp[now ^ 1][q][p], dp[now][j][k] + r);
					}
				}
				for (int r = 0; r <= c[i]; r++) {
					if (vc < r * money[i]) break;
					for (int l = 0; l <= r; l++) {
						int p = j + l * money[i];
						int q = k + (r - l) * money[i];
						if (p > MAXM || q > MAXM) continue;
						dp[now ^ 1][p][q] = min(dp[now ^ 1][p][q], dp[now][j][k] + r);
					}
				}
				for (int r = 0; r <= a[i]; r++) {
					int p = j - r * money[i];
					if (p < 0) break;
					for (int l = 0; l <= b[i]; l++) {
						int q = k - l * money[i];
						if (q < 0) continue;
						if (vc + (r + l) * money[i] > MAXM) continue;
						dp[now ^ 1][p][q] = min(dp[now ^ 1][p][q], dp[now][j][k] + r + l);
					}
				}
				for (int r = 0; r <= a[i]; r++) {
					int p = j - r * money[i];
					if (p < 0) break;
					for (int l = 0; l <= c[i]; l++) {
						int q = k + (l + r) * money[i];
						if (vc < l * money[i] || q > MAXM) continue;
						dp[now ^ 1][p][q] = min(dp[now ^ 1][p][q], dp[now][j][k] + r + l);
					}
				}
				for (int r = 0; r <= b[i]; r++) {
					int q = k - r * money[i];
					if (q < 0) break;
					for (int l = 0; l <= c[i]; l++) {
						int p = j + (l + r) * money[i];
						if (p > MAXM || vc < l * money[i]) continue;
						dp[now ^ 1][p][q] = min(dp[now ^ 1][p][q], dp[now][j][k] + r + l);
					}
				}
			}
		}
		now ^= 1;
	}
	if (dp[now][ea][eb] == INF) return -1;
	return dp[now][ea][eb];
}

int main() {
	freopen("1021.in", "r", stdin);
	scanf("%d %d %d", &x1, &x2, &x3);
	for (int i = 5; i >= 0; i--) scanf("%d", &a[i]);
	for (int i = 5; i >= 0; i--) scanf("%d", &b[i]);
	for (int i = 5; i >= 0; i--) scanf("%d", &c[i]);
	for (int i = 0; i < 6; i++) sa += a[i] * money[i], sb += b[i] * money[i], sc += c[i] * money[i];
	sum = sa + sb + sc;
	ea = sa - x1 + x3;
	eb = sb - x2 + x1;
	ec = sc - x3 + x2;
	int ans = solve();
	if (ans == -1) printf("impossible");
	else printf("%d\n", ans);
	return 0;
}
