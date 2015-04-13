#include <bits/stdc++.h>

using namespace std;

int n;
long long A;
long long d[200005], sum;

int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> A;
	for (int i = 0; i < n; i++) {
		cin >> d[i];
		sum += d[i];
	}
	for (int i = 0; i < n; i++) {
		int ans = 0;
		if (A - sum + d[i] > 1) ans += min(d[i] - 1, A - sum + d[i] - 1);
		if (A - n + 1 < d[i]) ans += d[i] - A + n - 1;
		cout << ans << " \n"[i == n - 1];
	}
	return 0;
}
