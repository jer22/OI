#include <bits/stdc++.h>

using namespace std;

const int MAXK = 250005;

long long n;
int k, m;
long long arr[MAXK];

bool check(long long x) {
	for (int i = 1; i <= m; i++) {
		// cout << arr[i] << " \n"[i == m];
		if (!(arr[i] % x)) return false;
	}
	return true;
}

int main() {
	freopen("2277.in", "r", stdin);
	scanf("%lld %d", &n, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%lld", &arr[i]);
		arr[i] = __gcd(arr[i], n);
	}
	sort(arr + 1, arr + k);
	m = unique(arr + 1, arr + k) - arr - 1;
	long long ans = LONG_LONG_MAX;
	for (long long i = 1; i * i <= arr[k]; i++) {
		if (arr[k] % i) continue;
		if (check(i)) ans = min(ans, i);
		if (check(arr[k] / i)) ans = min(ans, arr[k] / i);
	}
	printf("%lld\n", n / ans);

	return 0;
}
