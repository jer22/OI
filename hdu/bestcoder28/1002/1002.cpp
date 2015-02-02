#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

#define MOD 999991

using namespace std;

int T;
int n;
int f[50];
bool vis[999991];
// map<int, bool> vis;
int cnt;
int init() {
	vis[1] = vis[2] = vis[0] = 1;
	int i = 1;
	while (f[i] > 0 && f[i] < 1000000000) {
		f[i + 1] = f[i] + f[i - 1];
		i++;
		vis[f[i] % MOD] = 1;
	}
	return i - 1;
}

int main() {
	freopen("1002.in", "r", stdin);
	freopen("1", "w", stdout);
	scanf("%d", &T);
	f[0] = 1;
	f[1] = 2;
	cnt = init();
	// dfs(1, f[1]);
	while (T--) {
		scanf("%d", &n);
		// if (n == 0 || n == 1) {
		// 	printf("Yes\n");
		// 	continue;
		// }
		if (n == 999991) {
			printf("No\n");
			continue;
		}
		int i;
		for (i = 1; i <= cnt; i++) {
			if (f[i] > n) break;
		}
		i--;
		for (int j = i; j >= 1; j--) {
			// cout << j << endl;
			while (!(n % f[j])) n /= f[j];
		}

		if (vis[n % MOD]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
