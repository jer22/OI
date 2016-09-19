#include <bits/stdc++.h>

using namespace std;

long long n;
long long num[100005];

int main() {
	freopen("c.in", "r", stdin);
	cin >> n;
	num[0] = 2ll;
	for (long long i = 1ll; i <= n; i++) {
		long long a = (i + 1ll) * (i + 1ll);
		long long b = i;

		long long t = sqrt(b);
		long long x = a * b;
		num[i] = i * (i + 1ll);
		if (t * t == b) {
			x = a;
			num[i] = t * (i + 1ll);
		}
		cout << x - num[i - 1] / i << endl;
	}
	return 0;
}
