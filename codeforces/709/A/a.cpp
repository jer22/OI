#include <bits/stdc++.h>

using namespace std;

int n;
long long b, d;
int main() {
	freopen("a.in", "r", stdin);
	long long a;
	cin >> n >> b >> d;
	int ans = 0;
	long long cur = 0;
	for (int i = 0; i < n; i++) {
		cin >> a;
		if (a > b) continue;
		cur += a;
		if (cur > d) {
			ans++;
			cur = 0;
		}
	}
	cout << ans << endl;

	return 0;
}
