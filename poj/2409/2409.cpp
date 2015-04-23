#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int c[105];
int pow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

bool vis[105];

int main() {
	freopen("2409.in", "r", stdin);
	while (~scanf("%d %d", &m, &n)) {
		if (!n && !m) break;
		for (int i = 1; i <= n; i++) {
			c[i] = gcd(i, n);
		}
		for (int i = 1; i <= n; i++) {
			if (n & 1) c[i + n] = n / 2 + 1;
			else {
				if (i & 1) c[i + n] = n / 2;
				else c[i + n] = n / 2 + 1;
			}
		}
		int ans = 0;
		for (int i = 1; i <= n << 1; i++)
			ans += pow(m, c[i]);
		ans /= n * 2;
		cout << ans << endl;
	}


	return 0;
}
