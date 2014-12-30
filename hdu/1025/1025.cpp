#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[500005];
int idx[500005];
int dp[500005];
int maxlen = 0;
int DP(int num) {
	int l = 0, r = maxlen;
	while (l < r) {
		int m = (l + r >> 1) + 1;
		if (dp[m] > num)
			r = m - 1;
		else l = m;
	}
	if (!dp[l + 1]) maxlen++;
	return l + 1;
}

int main() {
	freopen("1025.in", "r", stdin);
	int cas = 1;
	while (~scanf("%d", &n)) {
		int a, b;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &a, &b);
			arr[b] = a;
		}
		maxlen = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			// arr[i] = idx[arr[i]];
			int k = DP(arr[i]);
			dp[k] = arr[i];
		}
		if (maxlen == 1)
			printf("Case %d:\nMy king, at most %d road can be built.\n\n", cas++, maxlen);
		else printf("Case %d:\nMy king, at most %d roads can be built.\n\n", cas++, maxlen);
	}


	return 0;
}
