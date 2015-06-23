#include <bits/stdc++.h>

using namespace std;


long long solve(long long a, long long b) {
	long long ans = 0;
	if (a == 1) return b;
	if (b == 1) return a;
	if (a > b) {
		long long t = a / b;
		ans += t;
		long long c = a - t * b;
		ans += solve(c, b);
	} else {
		long long t = b / a;
		ans += t;
		long long c = b - t * a;
		ans += solve(a, c);
	}
	return ans;
}

int main() {
	long long a, b;
	freopen("c.in", "r", stdin);
	cin >> a >> b;
	cout << solve(a, b) << endl;


	return 0;
}
