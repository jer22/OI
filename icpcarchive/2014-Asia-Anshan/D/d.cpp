#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 50005;

int T, n, k;
long long arr[MAXN], sum[MAXN];
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &arr[i]);
			sum[i] = sum[i - 1] + arr[i];
		}
		sort(arr + 1, arr + n + 1);
		for (int i = 1; i <= n; i++) {
			sum[i] = sum[i - 1] + arr[i];
		}
		long long now = 0;
		for (int i = 1; i <= n - k; i++) {
			now += arr[i] * arr[i] * (n - k);
		}
		now -= sum[n - k] * sum[n - k];
		long long mi = now;
		for (int i = n - k + 1; i <= n; i++) {
			now -= arr[i - n + k] * arr[i - n + k] * (n - k);
			now += arr[i] * arr[i] * (n - k);
			now += (sum[i - 1] - sum[i - n + k - 1]) * (sum[i - 1] - sum[i - n + k - 1]);
			now += (sum[i] - sum[i - n + k]) * (sum[i] - sum[i - n + k]);
			now -= 2ll * (sum[i] - sum[i - n + k]) * (sum[i] - sum[i - n + k]);
			mi = min(mi, now);
		}
		if (n == k) printf("0\n");
		else printf("%.10lf\n", (double)mi / (n - k));
	}


	return 0;
}
