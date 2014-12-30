#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n, m;
int v[999];
int w[999];
int dp[111];
int main() {
	freopen("2191.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		int a, b, c;
		int cnt = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			int base = 1;
			while (base <= c) {
				v[++cnt] = base * a;
				w[cnt] = base * b;
				c -= base;
				base <<= 1;
			}
			base >>= 1;
			if (base) {
				v[++cnt] = c * a;
				w[cnt] = c * b;
			}
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= cnt; i++) {
			for (int j = n; j >= v[i]; j--) {
				dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
			}
		}
		cout << dp[n] << endl;
	}


	return 0;
}
