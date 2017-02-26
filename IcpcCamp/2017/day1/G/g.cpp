#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

const int MAXN = 1000005;

int p;
int n, m;
struct Martrix{
	int a[5][5];
	Martrix() {
		memset(a, 0, sizeof(a));
	}
};

inline Martrix operator * (Martrix a, Martrix b) {
	Martrix c;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			long long res = 0;
			for (int k = 0; k < m; k++)
				res += (long long)a.a[i][k] * b.a[k][j];
			c.a[i][j] = res % p;
		}
	}
	
	return c;
}

Martrix a, b, ori;
Martrix ans[MAXN];
Martrix lef[MAXN], rig[MAXN];
int main() {
	freopen("g.in", "r", stdin);
	for (int i = 0; i < 5; i++) ori.a[i][i] = 1;
	while (~scanf("%d %d %d", &n, &m, &p)) {
		lef[1] = rig[1] = ori;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &a.a[i][j]);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &b.a[i][j]);
		int ll = 1, rr = 1;
		ans[0] = a;
		ans[1] = a * b;
		lef[++ll] = ans[1] * lef[ll - 1];
		lef[++ll] = ans[0] * lef[ll - 1];
		int c;
		scanf("%d", &c);
		int idx = 1;
		int l = 0;
		for (int i = 2; i <= n; i++) {
			scanf("%d", &c);
			if (c > idx) {
				ll = rr = 1;
				idx = i - 1;
				l = c;
				for (int j = i - 1; j >= l; j--)
					lef[++ll] = ans[j] * lef[ll - 1];
			} else {
				ll -= c - l;
				l = c;
			}
			ans[i] = lef[ll] * rig[rr] * b;
			rig[++rr] = rig[rr - 1] * ans[i];
		}
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				printf("%d%c", ans[n].a[i][j], " \n"[j == m - 1]);
	}


	return 0;
}
