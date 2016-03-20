#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int MOD = 1000000007;

int T, n, k;

long long sum(int l, int r) {
	long long a = l + r;
	long long b = r - l + 1;
	if (a & 1) return b / 2 * a;
	else return a / 2 * b;
}

int main() {
	freopen("a.in", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> n >> k;
		if (k > 50000 || sum(1, k) > (long long)n) {
			cout << -1 << endl;
			continue;
		}
		long long base = sum(1, k);
		int l = (n - base) / k + 1;
		int m = (n - base) % k;
		long long res = 1;
		for (int i = l; i <= l + k - 1 - m; i++)
			(res *= i) %= MOD;
		for (int i = l + k + 1 - m; i <= l + k; i++)
			(res *= i) %= MOD;
		cout << res << endl;
	}

	return 0;
}
