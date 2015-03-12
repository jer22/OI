#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

#define THIS (dp[k][x1][y1][x2][y2])

using namespace std;

int n;
int arr[11][11];
double sum[11][11];
double dp[17][11][11][11][11];

inline double S(int x1, int y1, int x2, int y2) {
	double t = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
	return t * t;
}

double dfs(int k, int x1, int y1, int x2, int y2) {
	if (k == 1) {
		THIS = S(x1, y1, x2, y2);
		return THIS;
	}
	if (fabs(THIS) > 1e-8) return THIS;
	THIS = 1 << 29;
	for (int i = x1; i < x2; i++) {
		THIS = min(THIS, min(dfs(k - 1, x1, y1, i, y2) + S(i + 1, y1, x2, y2),
			dfs(k - 1, i + 1, y1, x2, y2) + S(x1, y1, i, y2)));
	}
	for (int i = y1; i < y2; i++) {
		THIS = min(THIS, min(dfs(k - 1, x1, y1, x2, i) + S(x1, i + 1, x2, y2),
			dfs(k - 1, x1, i + 1, x2, y2) + S(x1, y1, x2, i)));
	}
	return THIS;
}

int main() {
	freopen("1191.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			cin >> arr[i][j];
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
	double adv = sum[8][8] / n;
	double ans = dfs(n, 1, 1, 8, 8) / n;
	printf("%.3lf\n", sqrt(ans - adv * adv));
	return 0;
}
