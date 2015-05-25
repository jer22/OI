#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

const double INF = 1e20;

double k1, k2;
int n, m;
double f[MAXN][MAXN][MAXN], g[MAXN][MAXN];
int lastk[MAXN][MAXN][MAXN], last[MAXN][MAXN][MAXN];

int main() {
	freopen("1505.in", "r", stdin);
	scanf("%lf %lf %d %d", &k1, &k2, &m, &n);
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			g[i][j] = INF;
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++)
			for (int k = 0; k < MAXN; k++)
				f[i][j][k] = INF;
	g[0][0] = 0;
	for (int i = 1; i <= 100; i++)
		for (int j = 1; j <= i; j++)
			for (int k = j - 1; k < i; k++)
				g[i][j] = min(g[i][j], g[k][j - 1] + (i - k) * (i - k) * k2);
	f[0][0][0] = 0;
	for (int k = 1; k <= 100; k++) {
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				for (int lk = lastk[k][i - 1][j]; lk < k; lk++) {
					for (int lj = last[k][i - 1][j]; lj < j; lj++) {
						if (f[lk][i - 1][lj] + (k - lk) * (k - lk) * k1 + g[k - lk][j - lj] < f[k][i][j]) {
							f[k][i][j] = f[lk][i - 1][lj] + (k - lk) * (k - lk) * k1 + g[k - lk][j - lj];
							lastk[k][i][j] = lk;
							last[k][i][j] = lj;
						}
					}
				}
			}
		}
	}
	printf("%.1lf\n", f[100][m][n]);

	return 0;
}
