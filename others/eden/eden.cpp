#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

int n, q, k;
int arr[55];
int m = 0;
int ans = 1;
void solve1() {
	int t;
	while (k != 1) {
		long long base = 1;
		while (base - 1 <= n) {
			base <<= 1;
		}
		base >>= 1;
		base -= 1;
		t = base / 2 + 1 + min(n - base, base / 2 + 1);
		if (k <= t) {
			n = t - 1;
			k--;
			ans <<= 1;
		} else {
			n -= t;
			k -= t;
			ans = ans << 1 | 1;
		}
	}
}

void solve2() {
	stack<int> s;
	int t = k;
	while (t) {
		s.push(t & 1);
		t >>= 1;
	}
	while (!s.empty()) {
		arr[m++] = s.top();
		s.pop();
	}
	for (int i = 1; i < m; i++) {
		long long base = 1;
		while (base - 1 <= n) {
			base <<= 1;
		}
		base >>= 1;
		base -= 1;
		t = base / 2 + 1 + min(n - base, base / 2 + 1);
		if (arr[i] == 0) {
			ans++;
			n = t - 1;
		} else {
			ans += t;
			n -= t;
		}
	}
}

int main() {
	freopen("eden.in", "r", stdin);
	cin >> n >> q >> k;
	if (q == 1) solve1();
	else solve2();
	cout << ans << endl;

	return 0;
}
