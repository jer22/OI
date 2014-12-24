#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int sx, sy, ex, ey;
int n;
int ans = 0;
int main() {
	// freopen("c.in", "r", stdin);
	cin >> sx >> sy >> ex >> ey;
	cin >> n;
	long long a, b, c;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		long long t1 = sx * a + sy * b + c;
		long long t2 = ex * a + ey * b + c;
		if (t1 > 0 && t2 < 0 || t1 < 0 && t2 > 0) ans++;
	}
	cout << ans << endl;
	return 0;
}
