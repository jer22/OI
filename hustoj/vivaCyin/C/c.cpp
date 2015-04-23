#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int T, n, m;
int arr[40005];
int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		int sum = 0, mx = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			mx = max(mx, arr[i]);
			sum += arr[i];
		}
		int t = min(n, m);
		int ans = sum / t;
		if ((sum % t)) ans++;
		ans = max(ans, mx);
		printf("%d\n", ans);
	}



	return 0;
}
