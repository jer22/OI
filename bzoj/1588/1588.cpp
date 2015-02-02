#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

#define INF 0x3f3f3f3f

using namespace std;

int n;
int siz, rt;
int t1, t2;
int fa[50005], num[50005], tr[50005][2];

void askBefore(int k, int x) {
	if (k == 0) return;
	if (num[k] <= x) {
		t1 = num[k];
		askBefore(tr[k][1], x);
	} else askBefore(tr[k][0], x);
}

void askAfter(int k, int x) {
	if (k == 0) return;
	if (num[k] >= x) {
		t2 = num[k];
		askAfter(tr[k][0], x);
	} else askAfter(tr[k][1], x);
}

void rotate(int x, int &k) {
	int y = fa[x], z = fa[y];
	int l, r;
	if (tr[y][0] == x) l = 0;
	else l = 1;
	r = l ^ 1;
	if (y == k) k = x;
	else {
		if (tr[z][0] == y) tr[z][0] = x;
		else tr[z][1] = x;
	}
	fa[x] = z;
	fa[y] = x;
	fa[tr[x][r]] = y;
	tr[y][l] = tr[x][r];
	tr[x][r] = y;
}

void splay(int x, int &k) {
	int y, z;
	while (x != k) {
		y = fa[x], z = fa[y];
		if (y != k) {
			if ((tr[y][0] == x) ^ (tr[z][0] == y)) rotate(x, k);
			else rotate(y, k);
		}
		rotate(x, k);
	}
}

void insert(int &k, int x, int last) {
	if (k == 0) {
		k = ++siz;
		num[k] = x;
		fa[k] = last;
		splay(k, rt);
		return;
	}
	if (x < num[k]) insert(tr[k][0], x, k);
	else insert(tr[k][1], x, k);
}

int main() {
	freopen("1588.in", "r", stdin);
	int x, ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		if (scanf("%d", &x) == EOF) x = 0;
		t1 = -INF, t2 = INF;
		askBefore(rt, x);
		askAfter(rt, x);
		if (i != 1) ans += min(x - t1, t2 - x);
		else ans += x;
		insert(rt, x, 0);
	}
	cout << ans << endl;
	return 0;
}
