#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 100005;

int T, n;
long long arr[MAXN];
int main() {
	// freopen("5935.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%lld", &arr[i]);
		int ans = 1;
		long long up = arr[n] - arr[n - 1];
		long long down = 1;
		for (int i = n - 1; i >= 1; i--) {
			long long s = arr[i] - arr[i - 1];
			long long now = s * down / up;
			if ((s * down) % up) now++;
			ans += now;
			up = s;
			down = now;
		}
		printf("Case #%d: %d\n", cas, ans);
	}
	return 0;
}
