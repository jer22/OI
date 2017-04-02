#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
long long arr[MAXN];
long long sum[MAXN];
long long mx[MAXN], mi[MAXN];

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	for (int i = 1; i < n; i++) {
		arr[i] = abs(arr[i] - arr[i + 1]) * (((i & 1) << 1) - 1);
		sum[i] = sum[i - 1] + arr[i];
	}
	mx[n] = -100000000000000000ll;
	mi[n] = 100000000000000000ll;
	for (int i = n - 1; i >= 1; i--) {
		mx[i] = max(mx[i + 1], sum[i]);
		mi[i] = min(mi[i + 1], sum[i]);
	}
	long long ans = -100000000000000000ll;
	for (int i = 1; i < n; i++) {
		if (i & 1) {
			ans = max(ans, mx[i] - sum[i - 1]);
		} else {
			ans = max(ans, sum[i - 1] - mi[i]);
		}
	}
	cout << ans << endl;


	return 0;
}
