#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 1000005;

int T, n;
int mob[MAXN];
void getMob() {
	for (int i = 1; i <= MAXN; i++) {
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= MAXN; j += i)
			mob[j] += delta;
	}
}
int main() {
	freopen("7001.in", "r", stdin);
	cin >> T;
	getMob();
	while (T--) {
		cin >> n;
		long long ans = 0;
		for (int i = 1; i <= n; i++)
			ans += (long long)mob[i] * (n / i) * (n / i) * (n / i);
		// ans -= n - 1
		for (int i = 1; i <= n; i++)
			ans += (long long)mob[i] * (n / i) * (n / i) * 3;
		cout << ans + 3 << endl;
	}


	return 0;
}
