#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define LCH l, m, rt << 1
#define RCH m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 11111;

int T;
int X[MAXN << 2];
int col[MAXN << 4];
int li[MAXN];
int ri[MAXN];
int hash[MAXN];
int cnt;
void pushDown(int rt) {
	if (col[rt] != -1) {
		col[rt << 1] = col[rt << 1 | 1] = col[rt];
		col[rt] = -1;
	}
}

int Bin(int key, int n) {
	int l = 0, r = n - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (X[m] == key) return m;
		if (X[m] < key) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

void update(int L, int R, int i, int l, int r, int rt) {
	if (L <= l && R >= r) {
		col[rt] = i;
		return;
	}
	pushDown(rt);
	int m = (l + r) >> 1;
	if (L <= m) update(L, R, i, LCH);
	if (R > m) update(L, R, i, RCH);
}

void query(int l, int r, int rt) {
	if (col[rt] != -1) {
		if (!hash[col[rt]]) cnt++;
		hash[col[rt]] = 1;
		return;
	}
	if (l == r) return;
	int m = (l + r) >> 1;
	query(LCH);
	query(RCH);
}

int main() {
	freopen("2528.in", "r", stdin);
	scanf("%d", &T);
	int n;
	while (T--) {
		scanf("%d", &n);
		int nn = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &li[i], &ri[i]);
			X[nn++] = li[i];
			X[nn++] = ri[i];
		}
		sort(X, X + nn);
		int siz = 1;
		for (int i = 1; i < nn; i++) {
			if (X[i] != X[i - 1]) X[siz++] = X[i];
		}
		for (int i = siz - 1; i >= 1; i--) {
			if (X[i] != X[i - 1] + 1) X[siz++] = X[i - 1] + 1;
		}
		sort(X, X + siz);
		memset(col, -1, sizeof(col));
		for (int i = 0; i < n; i++) {
			int l = Bin(li[i], siz);
			int r = Bin(ri[i], siz);
			update(l, r, i, 0, siz, 1);
		}
		cnt = 0;
		memset(hash, false, sizeof(hash));
		query(0, siz, 1);
		printf("%d\n", cnt);
	}

	return 0;
}
