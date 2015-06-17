/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <bits/stdc++.h>

using namespace std;

int n, m;
int t[105][305][305];
int val[305][305];

int lowbit(int x) {
	return x & -x;
}

void update(int x, int y, int col, int d) {
	for (int i = x; i <= n; i += lowbit(i))
		for (int j = y; j <= m; j += lowbit(j))
			t[col][i][j] += d;
}

int getsum(int x, int y, int col) {
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			ans += t[col][i][j];
	return ans;
}

int main() {
	freopen("1452.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int x, q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &val[i][j]);
			update(i, j, val[i][j], 1);
		}
	}
	scanf("%d", &q);
	int a, b, c, d, e;
	for (int i = 0; i < q; i++) {
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d %d %d", &a, &b, &c);
			update(a, b, val[a][b], -1);
			val[a][b] = c;
			update(a, b, c, 1);
		} else {
			scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
			int ans = getsum(b, d, e) + getsum(a - 1, c - 1, e) - getsum(a - 1, d, e) - getsum(b, c - 1, e);
			printf("%d\n", ans);
		}
	}

	return 0;
}
