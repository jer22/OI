#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

int n;
int dp[4205][2];
int ans = 0;
bool vis[25];
void dfs(int step, int num, bool f) {
	if (step == n) {
		ans++;
		return;
	}
	if (!f) {
		for (int i = num + 1; i <= n; i++) {
			if (vis[i]) continue;
			vis[i] = 1;
			dfs(step + 1, i, f ^ 1);
			vis[i] = 0;
		}
	} else {
		for (int i = 1; i < num; i++) {
			if (vis[i]) continue;
			vis[i] = 1;
			dfs(step + 1, i, f ^ 1);
			vis[i] = 0;
		}
	}

}

int main() {
	freopen("1925.in", "r", stdin);
	for (n = 2; n <= 100; n++) {
		ans = 0;
		for (int i = 1; i <= n; i++) {
			memset(vis, 0, sizeof(vis));
			vis[i] = 1;
			dfs(1, i, 0);
			memset(vis, 0, sizeof(vis));
			vis[i] = 1;
			dfs(1, i, 1);
		}

		cout << ans << endl;
	}


	return 0;
}
