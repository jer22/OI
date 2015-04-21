#include <bits/stdc++.h>

using namespace std;

const long long INF = 1000000000000000000;

int n;
long long a, b, c, d, mod;
long long arr[5000005];

inline long long f(long long x) {
	x %= mod;
	int aa = (((((x * x) % mod) * x) % mod) * a) % mod;
	int bb = (((x * x) % mod) * b) % mod;
	int cc = (x * c) % mod;
	return (((aa + bb) % mod + cc) % mod + d) % mod;
}

inline void generate() {
	a %= mod;
	b %= mod;
	c %= mod;
	d %= mod;
	arr[1] %= mod;;
	for (int i = 2; i <= n; i++)
		arr[i] = (f(arr[i - 1]) % mod + f(arr[i - 2]) % mod) % mod;
}

long long brr[5000005];
bool solve(long long mid) {
	brr[0] = -INF;
	for (int i = 1; i <= n; i++) {
		if (arr[i] >= brr[i - 1]) {
			brr[i] = max(brr[i - 1], arr[i] - mid);
		} else {
			if (arr[i] + mid < brr[i - 1]) return false;
			brr[i] = brr[i - 1];
		}
	}
	return true;
}

int main() {
	freopen("3613.in", "r", stdin);
	cin >> n >> a >> b >> c >> d >> arr[1] >> mod;
	generate();
	long long l = 0, r = INF;
	while (l < r) {
		// cout << l << ' ' << r << endl;
		long long mid = l + r >> 1;
		if (solve(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", l);

	return 0;
}
