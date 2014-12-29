#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int up[1005][1005];
int cnt[1005];
int main() {
	freopen("2830.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		char c;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> c;
				if (c == '1') up[i][j] = up[i - 1][j] + 1;
				else up[i][j] = 0;
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			memset(cnt, 0, sizeof(cnt));
			for (int j = 1; j <= m; j++)
				cnt[up[i][j]]++;
			for (int j = n; j >= 1; j--)
				cnt[j] += cnt[j + 1];
			for (int j = 1; j <= n; j++)
				ans = max(ans, j * cnt[j]);
		}
		cout << ans << endl;
	}

	return 0;
}
