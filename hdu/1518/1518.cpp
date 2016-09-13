#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n;
int arr[25];
bool vis[25];
int totlen;

bool dfs(int pos, int len, int cnt) {
	// cout << pos << ' ' << len << ' ' << cnt << endl;
	if (cnt == 4) return true;
	for (int i = pos; i >= 1; i--) {
		if (vis[i]) continue;
		if (len + arr[i] < totlen) {
			vis[i] = 1;
			if (dfs(i - 1, len + arr[i], cnt)) return true;
			vis[i] = 0;
		} else if (len + arr[i] == totlen) {
			vis[i] = 1;
			if (dfs(n - 1, 0, cnt + 1)) return true;
			vis[i] = 0;
			return false;
		}
	}
	return false;
}

int main() {
	freopen("1518.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			sum += arr[i];
		}

		totlen = sum / 4;
		if (sum % 4) {
			printf("no\n");
			continue;
		}
		if (arr[n] > totlen) {
			printf("no\n");
			continue;
		}
		sort(arr + 1, arr + n + 1);
		memset(vis, 0, sizeof(vis));
		bool ans;
		if (arr[n] == totlen) {
			ans = dfs(n - 1, 0, 1);
		} else ans = dfs(n, 0, 0);
		if (ans) printf("yes\n");
		else printf("no\n");
	}



	return 0;
}
