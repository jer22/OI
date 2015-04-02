#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int edges[105][105];
long long tot[105][105];
double ans[105];
int main() {
	freopen("1491.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b, c;
	memset(edges, 0x3f, sizeof(edges));
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a][b] = c;
		edges[b][a] = c;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (edges[i][j])
				tot[i][j] = 1;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == k || j == k || i == j) continue;
				if (edges[i][k] + edges[k][j] == edges[i][j]) {
					tot[i][j] += tot[i][k] * tot[k][j];
				} else if (edges[i][k] + edges[k][j] < edges[i][j]) {
					edges[i][j] = edges[i][k] + edges[k][j];
					tot[i][j] = tot[i][k] * tot[k][j];
				}
			}
		}
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j || i == k || j == k) continue;
				if (edges[i][k] + edges[k][j] == edges[i][j])
					ans[k] += double(tot[i][k] * tot[k][j]) / double(tot[i][j]);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%.3lf\n", ans[i]);

	return 0;
}
