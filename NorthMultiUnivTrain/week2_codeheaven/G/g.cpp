#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

bool pri[1000005];
int p[1000005], num = 0, tot = 0;
int fa[MAXN], pos[1000005];
int minfac[1000005];
int fin(int p) {
	if (p == fa[p]) return p;
	return fa[p] = fin(fa[p]);
}
void un(int a, int b) {
	fa[fin(a)] = fin(b);
}

void init() {
	for (int i = 2; i <= 1000000; i++) {
		if (!pri[i]) {
			minfac[i] = i;
			p[++num] = i;
			pos[i] = num;
		}
		for (int j = 1; j <= num; j++) {
			if(i * p[j] > 1000000) break;
			pri[i * p[j]] = 1;
			minfac[p[j] * i] = p[j];
		}
	}
	// for (int i = 2; i <= 1000000; i++) {
	// 	int x = i;
	// 	while (x > 1) {
	// 		int t = minfac[x];
	// 		fac[i].push_back(t);
	// 		while (!(x % t)) x /= t;
	// 	}
	// }

}

bool vis[MAXN], vv[MAXN];
int main() {
	freopen("g.in", "r", stdin);
	// freopen("out", "w", stdout);
	init();
	int T, n;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d", &n);
		for (int i = 1; i <= num; i++) {
			vis[i] = vv[i] = 0;
			fa[i] = i;
		}
		int ans = 0;
		int x;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			if (x == 1) ans++;
			int pre = 0;
			while (x > 1) {
				int t = minfac[x];
				vis[pos[t]] = 1;
				if (pre) {
					un(pre, pos[t]);
				}
				pre = pos[t];
				while (!(x % t)) x /= t;
			}
		}

		for (int i = 1; i <= num; i++) {
			if (!vis[i]) continue;
			int p = fin(i);
			if (!vv[p]) {
				ans++;
				vv[p] = 1;
			}
		}
		printf("Case %d: %d\n", cas, ans);
	}


	return 0;
}
