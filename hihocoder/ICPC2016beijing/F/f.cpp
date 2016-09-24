#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <complex>
#include <climits>
#include <vector>

#define E complex<long double>

using namespace std;

const long long MAXN = 150005ll;
const long long INF = 1e18;
const long double pi = acos(-1.0);

long long T, n, m, L;
long long arr[MAXN], brr[MAXN];
long long r[MAXN];
long long c[MAXN];
E a[MAXN], b[MAXN];

void fft(E *a, long long f) {
	for (long long i = 0ll; i < n; i++)
		if (i < r[i]) swap(a[i], a[r[i]]);
	for (long long i = 1ll; i < n; i <<= 1ll) {
		E wn(cos(pi / i), f * sin(pi / i));
		for (long long j = 0ll; j < n; j += (i << 1ll)) {
			E w(1.0, 0.0);
			for (long long k = 0ll; k < i; k++, w *= wn) {
				E x = a[j + k];
				E y = w * a[j + k + i];
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
	if (f == -1ll) for (long long i = 0ll; i < n; i++) a[i] /= n;
}
long long t;
long long getsum(int k) {
	long long ans = 0ll;
	for (int i = 0; i < t; i++)
		ans += (arr[i] - brr[(i + k) % t]) * (arr[i] - brr[(i + k) % t]);
	return ans;
}
int main() {
	freopen("f.in", "r", stdin);
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld", &n);
		long long tot = 0;
		for (long long i = 0; i < n; i++)
			scanf("%lld", &arr[i]);
		for (long long i = 0; i < n; i++)
			scanf("%lld", &brr[i]);
		for (long long i = 0; i < n; i++)
			tot += arr[i] * arr[i] + brr[i] * brr[i];
		t = n;
		n--;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for (long long i = 0; i <= n; i++)
			a[i] = arr[i];
		for (long long i = 0; i <= n; i++)
			b[i] = brr[n - i];
		m = n << 1;
		L = 0;
		memset(r, 0, sizeof(r));
		for (n = 1; n <= m; n <<= 1) L++;
		for (long long i = 0; i < n; i++)
			r[i] = (r[i >> 1ll] >> 1ll) | ((i & 1ll) << (L - 1ll));
		fft(a, 1ll);
		fft(b, 1ll);
		for (long long i = 0; i < n; i++) a[i] *= b[i];
		fft(a, -1ll);
		memset(c, 0, sizeof(c));
		for (long long i = 0; i <= m; i++) {
			c[i] = (long long)(a[i].real() + 0.4);
		}

		vector<pair<long long, int> > ans;
		for (long long i = 0; i < t; i++)
			ans.push_back(make_pair(tot - c[i] - c[i + t], i));
		sort(ans.begin(), ans.end());
		long long ret = tot;
		for (int i = 0; i < min(500ll, t); i++) {
			// cout << ans[i].second << endl;
			ret = min(ret, getsum(ans[i].second));
			// cout << ans[i].second << endl;
		}
		// cout << ret - 2 * ans << endl;
		printf("%lld\n", ret);

	}
	return 0;
}
