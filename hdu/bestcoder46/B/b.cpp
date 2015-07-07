#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[1005];
bool vis[1005][1005];
int main() {
	freopen("b.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		int a, b;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &a, &b);
			edges[i].clear();
		}
		if (!m) {
			printf("1 %d\n", n);
			continue;
		}
		memset(vis, 0, sizeof(vis));
		int cnt4 = 0, cnt3 = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
			vis[a][b] = vis[b][a] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				int x = edges[i][j];
				for (int k = 0; k < edges[i].size(); k++) {
					if (j == k) continue;
					int y = edges[i][k];
					if (vis[x][y]) {
						cnt3++;
						for (int l = 1; l <= n; l++) {
							if (vis[i][l] && vis[x][l] && vis[y][l]) cnt4++;
						}
					}
				}
			}
		}
		if (cnt4) printf("4 %d\n", cnt4 / 24);
		else if (cnt3) printf("3 %d\n", cnt3 / 6);
		else printf("2 %d\n", m);
	}


	return 0;
}
