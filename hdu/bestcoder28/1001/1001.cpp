#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n;
int vis[1005];
int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int x;
		int ma = 0;
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			vis[x] = 1;
			ma = max(ma, x);
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				cnt++;
				if (cnt != 1) printf(" ");
				printf("%d", i);
			}
		}
		if (!cnt) printf("%d %d", ma + 1, ma + 2);
		else if (cnt == 1) printf(" %d", ma + 1);
		printf("\n");
	}

	return 0;
}
