#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n, m;
int arr[105];
int main() {
	// freopen("5968.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			// arr[i] ^= arr[i - 1];
		}
		scanf("%d", &m);
		int x;
		while (m--) {
			int ans = 0, best = 0x3f3f3f3f;
			scanf("%d", &x);
			for (int i = 1; i <= n; i++) {
				int now = 0;
				for (int j = i; j <= n; j++) {
					now ^= arr[j];
					if (abs(now - x) < best) {
						best = abs(now - x);
						ans = j - i + 1;
					} else if (abs(now - x) == best) ans = max(ans, j - i + 1);
				}
			}
			printf("%d\n", ans);
		}
		printf("\n");
	}
	return 0;
}
