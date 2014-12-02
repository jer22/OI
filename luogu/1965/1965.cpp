#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;



int main() {
	/*freopen("1965.in", "r", stdin);*/
	long long n, m, k, x;
	cin >> n >> m >> k >> x;
	long long a = 10;
	long long ans = m;
	while (k) {
		if (k & 1) {
			ans = ans * a % n;
		}
		a = a * a % n;
		k >>= 1;
	}
	ans = (ans + x % n) % n;
	cout << ans;
	return 0;
}
