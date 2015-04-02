#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
char str[15][15];
int score[15][15];

int getscore(char *a, char *b) {
	int lena = strlen(a);
	int lenb = strlen(b);
	int ans = 0, mx = 0;
	for (int i = 0; i < lena; i++) {
		ans = 0;
		for (int j = i; j < min(lena, lenb + i); j++)
			if (a[j] == b[j - i]) ans++;
		mx = max(mx, ans);
	}
	for (int i = 0; i < lenb; i++) {
		ans = 0;
		for (int j = i; j < min(lenb, lena + i); j++)
			if (a[j - i] == b[j]) ans++;
		mx = max(mx, ans);
	}
	return mx;
}

bool vis[15];
int ans = 0;
void dfs(int step, int i, int sc) {
	if (sc + 10 * (n - step) <= ans) return;
	if (step == n) {
		ans = max(ans, sc);
		return;
	}
	for (int j = 1; j <= n; j++) {
		if (!vis[j]) {
			vis[j] = 1;
			dfs(step + 1, j, sc + score[i][j]);
			vis[j] = 0;
		}
	}

}

int main() {
	freopen("2817.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (n <= 0) break;
		ans = 0;
		for (int i = 1; i <= n; i++)
			scanf("%s", str[i]);
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				score[i][j] = score[j][i] = getscore(str[i], str[j]);
		memset(vis, 0, sizeof(vis));
		dfs(0, 0, 0);
		printf("%d\n", ans);
	}

	return 0;
}
