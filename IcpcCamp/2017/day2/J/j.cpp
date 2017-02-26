#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 105;

int n, k;

int main() {
	// freopen("j.in", "r", stdin);
	while (~scanf("%d %d", &n, &k)) {
		if (k == 1) {
			printf("-1\n");
			continue;
		}
		vector<pii > ans;
		if (k & 1) {
			for (int i = 1; i <= n + 1 >> 1; i++) {
				ans.push_back(mp(i, i + (n >> 1)));
			}
			k--;
		}
		for (int i = 1; i < n; i++)
			ans.push_back(mp(i, i + 1));
		ans.push_back(mp(n, 1));
		for (int j = 2; j <= k >> 1; j++) {
			for (int i = 1; i <= n; i++) {
				int f = i + j;
				if (f > n) f -= n;
				ans.push_back(mp(i, f));
			}
		}
		printf("%d\n", (int)ans.size());
		for (int i = 0; i < ans.size(); i++) {
			printf("%d %d\n", ans[i].first, ans[i].second);
		}
		for (int i = 1; i <= n; i++)
			printf("%d%c", i, " \n"[i == n]);
	}


	return 0;
}
