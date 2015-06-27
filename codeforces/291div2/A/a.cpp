#include <bits/stdc++.h>

using namespace std;

long long n;
int ans[20];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	int ed = 19;
	while (n) {
		int x = n % 10;
		n /= 10;
		ans[ed--] = min(x, 9 - x);
	}
	if (ans[ed + 1] == 0) ans[ed + 1] = 9;
	for (int i = ed + 1; i <= 19; i++) {
		cout << ans[i];
	}
	cout << endl;
	return 0;
}
