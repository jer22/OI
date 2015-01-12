#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int edges[28][28];
int cnt[28];
int ans[28];
int main() {
	freopen("1094.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		if (!n && !m) break;
		getchar();
		memset(edges, 0, sizeof(edges));
		char a, b, t;
		bool flag = true;
		for (int tt = 1; tt <= m; tt++) {
			scanf("%c%c%c\n", &a, &t, &b);
			if (!flag) continue;
			if (edges[a - 'A'][b - 'A']) continue;
			edges[a - 'A'][b - 'A'] = 1;
			for (int k = 0; k < n; k++) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						edges[i][j] = max(edges[i][j], (edges[i][k] & edges[k][j]));
						if (edges[i][j] && edges[j][i])
							flag = false;
					}
				}
			}
			if (!flag) {
				printf("Inconsistency found after %d relations.\n", tt);
				continue;
			}
			memset(cnt, 0, sizeof(cnt));
			memset(ans, 0, sizeof(ans));
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (edges[i][j]) cnt[i]++;
				}
			}
			bool f = true;
			for (int i = 0; i < n; i++) {
				ans[cnt[i]]++;
				if (ans[cnt[i]] > 1) {
					f = false;
					break;
				}
			}
			if (f) {
				flag = false;
				int res[28];
				for (int i = 0; i < n; i++) {
					res[n - cnt[i] - 1] = i;
				}
				printf("Sorted sequence determined after %d relations: ", tt);
				for (int i = 0; i < n; i++)
					printf("%c", res[i] + 'A');
				printf(".\n");
			}
		}
		if (!flag) continue;
		printf("Sorted sequence cannot be determined.\n");
	}

	return 0;
}
