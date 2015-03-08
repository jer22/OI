#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int n, k, T;
long long arr[1000005];
long long sum[1000005];
bool vis[1000007];
int main() {
	freopen("1002.in", "r", stdin);
	int cas = 1;
	scanf("%d", &T);
	while (T--) {
		memset(vis, 0, sizeof(vis));
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; i++) {
			sum[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &arr[i]);
			if (i % 2) sum[i] += arr[i];
			else sum[i] -= arr[i];
			vis[sum[i] % 1000007] = 1;
		}
		bool flag = false;
		for (int i = 1; i <= n; i += 2) {
			long long a = sum[i - 1];
			if (vis[(a + k) % 1000007]) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			for (int i = 2; i <= n; i += 2) {
				long long a = sum[i - 1];
				if (vis[(a - k) % 1000007]) {
					flag = true;
					break;
				}
			}
		}
		if (flag) printf("Case #%d: Yes.\n", cas++);
		else printf("Case #%d: No.\n", cas++);
	}

	return 0;
}
