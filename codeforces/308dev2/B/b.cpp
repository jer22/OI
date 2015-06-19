#include <bits/stdc++.h>

using namespace std;

int n;
long long f[12];
long long t[12];
int main() {
	cin >> n;
	t[1] = 10;
	for (int i = 2; i <= 10; i++)
		t[i] = t[i - 1] * 10;
	f[1] = 11;
	for (int i = 2; i <= 10; i++)
		f[i] = f[i - 1] + (t[i] - t[i - 1]) * i + 1;
	long long ans;
	long long base;
	for (int i = 0; i <= n; i++) {
		if (t[i] > n) {
			base = i - 1;
			break;
		}
	}
	ans = f[base] + (n - t[base]) * (base + 1);
	cout << ans << endl;
	return 0;
}
