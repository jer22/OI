#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int edges[111][111];

int main() {
	freopen("1001.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		int a, b;
		memset(edges, 0, sizeof(edges));
		bool ans = true;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[a][b] = 1;
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					edges[i][j] = max(edges[i][j], edges[i][k] & edges[k][j]);
		for (int i = 1; i <= n; i++) {
			if (!ans) break;
			for (int j = 1; j <= n; j++) {
				if (edges[i][j] && edges[j][i]) {
					ans = false;
					break;
				}
			}
		}
		if (ans) printf("YES\n");
		else printf("NO\n");
	}
	

	return 0;
}
