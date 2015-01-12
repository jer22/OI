#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int edges[105][105];
int main() {
	freopen("1125.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		memset(edges, 0x3f, sizeof(edges));
		int t, a, b;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &t);
			for (int j = 1; j <= t; j++) {
				scanf("%d %d", &a, &b);
				edges[i][a] = b;
			}
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j]);
		int ans = 0x3f3f3f3f;
		int idx = 0;
		for (int i = 1; i <= n; i++) {
			int dist = 0;
			for (int j = 1; j <= n; j++)
				if (i != j) dist = max(dist, edges[i][j]);
			if (dist < ans) {
				ans = dist;
				idx = i;
			}
		}
		if (ans == 0x3f3f3f3f)
			printf("disjoint\n");
		else printf("%d %d\n", idx, ans);
	}


	return 0;
}
