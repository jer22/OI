#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, k;
long long sum[MAXN];
map<long long, int> cnt;
int main() {
	freopen("c.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &sum[i]);
		sum[i] += sum[i - 1];
	}
	cnt[sum[n]] = 1;
	long long ans = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (k == 1) {
			ans += cnt[sum[i] + 1];
		} else if (k == -1) {
			ans += cnt[sum[i] + 1] + cnt[sum[i] - 1];
		} else {
			for (long long f = 1ll; abs(f) <= 100000000000000ll; f *= k) {
				ans += cnt[sum[i] + f];
			}
		}
		cnt[sum[i]]++; 
	}
	printf("%lld\n", ans);

	return 0;
}
