#include <bits/stdc++.h>

using namespace std;

int T;
int sta[300] = {0, 0, 255, 15, 51, 85}, tot = 5;
bool vis[300];
int ans[300] = {1, 5, 6, 3, 6, 3, 7, 4, 7, 8, 4, 5, 4, 5, 4, 1, 6, 3, 7, 4, 7, 4, 9, 7, 8, 8, 7, 5, 7, 5, 7, 4, 7, 8, 4, 5, 8, 8, 7, 5, 8, 9, 5, 6, 8, 8, 5, 5, 4, 5, 4, 1, 7, 5, 7, 4, 8, 8, 5, 5, 5, 7, 6, 4, 7, 8, 8, 8, 4, 5, 7, 5, 8, 9, 8, 8, 5, 6, 5, 5, 4, 5, 7, 5, 4, 1, 7, 4, 8, 8, 5, 7, 5, 5, 6, 4, 8, 9, 8, 8, 8, 8, 5, 7, 11, 9, 8, 9, 8, 9, 8, 8, 5, 6, 5, 5, 5, 5, 6, 4, 8, 9, 8, 8, 8, 8, 8, 7, 8, 9, 9, 9, 9, 9, 10, 9, 5, 7, 6, 6, 6, 6, 7, 6, 9, 9, 10, 9, 10, 9, 10, 10, 7, 6, 7, 7, 7, 7, 9, 7, 5, 7, 6, 6, 7, 6, 7, 7, 5, 6, 2, 3, 6, 6, 4, 3, 6, 6, 7, 6, 7, 7, 9, 7, 6, 6, 4, 3, 7, 7, 7, 6, 5, 7, 7, 6, 6, 6, 7, 7, 5, 6, 6, 6, 2, 3, 4, 3, 6, 6, 7, 7, 7, 6, 9, 7, 6, 6, 7, 7, 4, 3, 7, 6, 5, 6, 6, 6, 6, 6, 7, 7, 8, 9, 5, 6, 5, 6, 2, 5, 2, 3, 4, 3, 4, 3, 7, 6, 5, 6, 2, 5, 2, 5, 4, 1};

inline int nand(int a, int b) {
	return (255 ^ (a & b));
}
bool dfs(int dep, int des, int mx) {
	// cout << dep << endl;
	if (vis[des]) return true;
	if (dep >= mx) return false;
	bool tmp[300];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 1; i <= tot; i++) {
		for (int j = i + 1; j <= tot; j++) {
			int k = nand(sta[i], sta[j]);
			if (!vis[k] && !tmp[k]) {
				tmp[k] = 1;
				vis[k] = 1;
				sta[++tot] = k;
				if (dfs(dep + 1, des, mx)) return true;
				vis[k] = 0;
				tot--;
			}
		}
	}
	return false;
}

int main() {
	freopen("h.in", "r", stdin);
	// freopen("table", "w", stdout);
	// for (int i = 0; i < 256; i++) {
	// 	int st = 0;
	// 	memset(vis, 0, sizeof(vis));
	// 	vis[0] = vis[255] = vis[15] = vis[51] = vis[85] = 1;
	// 	tot = 5;
	// 	while (st <= 10 && !dfs(0, i, st)) {
	// 		st++;
	// 		memset(vis, 0, sizeof(vis));
	// 		vis[0] = vis[255] = vis[15] = vis[51] = vis[85] = 1;
	// 		tot = 5;
	// 	}
	// 	ans[i] = st;
	// 	cout << i << ' ' << st << endl;
	// }
	char str[10];
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str);
		int p = 0;
		for (int i = 0; i < 8; i++)
			p = p << 1 | (str[i] - '0');
		cout << ans[p] << endl;
	}


	return 0;
}
