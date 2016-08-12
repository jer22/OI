#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n, m;
int a[1005], b[1005];
int qry[1005][2];
int nex[1005], vis[1005];
int cnta[1005], cntb[1005];

int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		memset(cnta, 0, sizeof(cnta));
		memset(cntb, 0, sizeof(cntb));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			cnta[a[i]]++;
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &b[i]);
			cntb[b[i]]++;
		}
		for (int i = 0; i < m; i++)
			scanf("%d %d", &qry[i][0], &qry[i][1]);
		bool flag = 0;
		for (int i = 1; i <= n; i++) {
			if (cnta[i] != cntb[i]) {
				printf("No\n");
				flag = 1;
				break;
			}
		}
		if (flag) continue;
		memset(vis, 0, sizeof(vis));
		memset(nex, 0, sizeof(nex));
		for (int i = 1; i <= n; i++) {
			if (!a[i]) continue;
			for (int j = 1; j <= n; j++) {
				if (vis[j]) continue;
				if (a[i] == b[j]) {
					nex[i] = j;
					vis[j] = 1;
					break;
				}
			}
		}
		flag = 1;
		for (int i = 1; i <= n; i++) {
			if (!a[i]) continue;
			int l = i, r = i;
			// cout << nex[i] << endl;
			for (int j = 0; j < m; j++) {
				if (qry[j][0] <= r && qry[j][1] >= l) {
					l = min(l, qry[j][0]);
					r = max(r, qry[j][1]);
				}
			}
			if (l <= nex[i] && r >= nex[i]) {
				// cout << 'f';
			} else {
				flag = 0;
			}
		}
		if (!flag) printf("No\n");
		else printf("Yes\n");
	}



	return 0;
}
