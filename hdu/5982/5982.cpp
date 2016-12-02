#include <bits/stdc++.h>

using namespace std;

int T, n, a, b;
int main() {
	freopen("5982.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		int ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			ans += a * b;
		}
		printf("%d\n", ans);
	}

	return 0;
}
