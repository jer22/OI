#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int allo[50005][4];
int reqe[50005][4];
long long pool[4];
int vis[50005];
int main() {
	freopen("2474.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &allo[j][i]);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &reqe[j][i]);
		for (int i = 1; i <= m; i++)
			scanf("%I64d", &pool[i]);
		memset(vis, 0, sizeof(vis));
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			bool flag = false;
			for (int j = n; j >= 1; j--) {
				if (vis[j]) continue;
				bool can = true;
				for (int k = 1; k <= m; k++)
					if (reqe[j][k] > pool[k]) can = false;
				if (can) {
					cnt++;
					vis[j] = 1;
					flag = true;
					for (int k = 1; k <= m; k++)
						pool[k] += allo[j][k];
				}
			}
			if (cnt == n) {
				cout << "Yes" << endl;
				break;
			}
			if (!flag) {
				cout << "No" << endl;
				break;
			}
		}
	}

	return 0;
}
