#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[505];
int brr[1005];
int vis[505];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &brr[i]);
	}
	int ans = 0;
	for (int i = 2; i <= m; i++) {
		memset(vis, 0, sizeof(vis));
		for (int j = i - 1; j >= 1; j--) {
			if (brr[j] == brr[i]) break;
			if (!vis[brr[j]]) {
				vis[brr[j]] = 1;
				ans += arr[brr[j]];
			}
		}
	}
	cout << ans << endl;
	return 0;
}
