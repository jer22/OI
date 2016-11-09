#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

const int MAXN = 40005;

using namespace std;

int T, n, m;
int cnt[MAXN];
map<pii, int> vis;
int main() {
	// freopen("5963.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		memset(cnt, 0, sizeof(cnt));
		vis.clear();
		int a, b, c;
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			if (a > b) swap(a, b);
			if (c) cnt[a]++, cnt[b]++;
			vis[mp(a, b)] = c;
		}
		int op;
		for (int i = 0; i < m; i++) {
			scanf("%d", &op);
			if (op) {
				scanf("%d %d %d", &a, &b, &c);
				if (a > b) swap(a, b);
				if (vis[mp(a, b)] != c) {
					if (c) cnt[a]++, cnt[b]++;
					else cnt[a]--, cnt[b]--;
					vis[mp(a, b)] = c;
				}
			} else {
				scanf("%d", &a);
				if (cnt[a] & 1) printf("Girls win!\n");
				else printf("Boys win!\n");
			}
		}
	}
	return 0;
}
