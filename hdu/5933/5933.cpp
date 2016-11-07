#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 100005;

int T, n, m;
long long arr[MAXN];
int main() {
	// freopen("5933.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &m);
		long long sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &arr[i]);
			sum += arr[i];
		}
		if (sum % m) {
			printf("Case #%d: -1\n", cas);
			continue;
		}
		long long num = sum / m;
		int ans = 0;
		long long pre = 0;
		for (int i = 1; i <= n; i++) {
			while (arr[i] > num) {
				ans++;
				arr[i] -= num;
			}
			if (arr[i] < num) {
				ans++;
				arr[i + 1] += arr[i];
			}
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}
