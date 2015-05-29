#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int T;
long long n, m, k;
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%lld %lld %lld", &n, &m, &k);
		printf("Case #%d: ", cas++);
		long long ans = 0;
		long long a = n * m * k - 1;
		while (n > 1) {
			ans++;
			n = (n + 1) / 2;
		}
		while (m > 1) {
			ans++;
			m = (m + 1) / 2;
		}
		while (k > 1) {
			ans++;
			k = (k + 1) / 2;
		}

		printf("%lld %lld\n", a, ans);
	}



	return 0;
}
