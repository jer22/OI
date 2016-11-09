#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int T;
long long n, m, p;
long long g[705][705], c[705][705];

void fuck(int i, int j) {
	int tt = 0, x = i, y = j;
	while (y) {
		tt++;
		int t = x % y;
		x = y;
		y = t;
	}
	c[i][j] = tt;
	g[i][j] = x;
}

void init() {
	for (int i = 1; i <= 670; i++)
		for (int j = 1; j <= 670; j++)
			fuck(i, j);
}

bool vis[33];
vector<long long> mo;
int main() {
	// freopen("5970.in", "r", stdin);
	scanf("%d", &T);
	init();
	while (T--) {
		scanf("%lld %lld %lld", &n, &m, &p);
		long long ans = 0;
		for (int j = 1; j <= m; j++) {
			for (int i = 1; i <= j; i++) {
				if (i > n) break;
				long long num = (n - i) / j + 1;
				long long gcd = g[i][j];
				long long cnt = c[i][j];
				long long a0 = (i / gcd) * (j / gcd);
				long long dif = (j / gcd) * (j / gcd);
				long long tot = a0 * num + (num * (num - 1)) / 2 * dif;
				memset(vis, 0, sizeof(vis));
				mo.clear();
				long long tmp = a0 % cnt;
				while (!vis[tmp]) {
					vis[tmp] = 1;
					mo.push_back(tmp);
					tmp = (tmp + dif) % cnt;
				}
				int sz = mo.size();
				for (int i = 0; i < sz; i++)  {
					long long t = num / sz + (i < num % sz);
					tot -= mo[i] * t;
				}
				tot /= cnt;
				ans += tot;
				ans %= p;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
