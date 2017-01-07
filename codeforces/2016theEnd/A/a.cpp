#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
int main() {
	freopen("a.in", "r", stdin);
	cin >> n >> k;
	int ans = 0;
	int now = k;
	for (int i = 1; i <= n; i++) {
		now += i * 5;
		if (now <= 240) ans++;
		else break;
	}
	cout << ans << endl;
	return 0;
}
