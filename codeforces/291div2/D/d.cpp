#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch
#define roo 1, n, 1

using namespace std;

int n, m, k;
int arr[6][100005];
int tmp[6][400005];
int res[6];

void pushUp(int rt, int i) {
	tmp[i][rt] = max(tmp[i][lch], tmp[i][rch]);
}

void build(int i, int l, int r, int rt) {
	if (l == r) {
		tmp[i][rt] = arr[i][l];
		return;
	}
	int m = l + r >> 1;
	build(i, lson);
	build(i, rson);
	pushUp(rt, i);
}

int query(int L, int R, int l, int r, int rt, int i) {
	if (L <= l && R >= r) {
		return tmp[i][rt];
	}
	int m = l + r >> 1;
	int ans = 0;
	if (L <= m) ans = max(ans, query(L, R, lson, i));
	if (R > m) ans = max(ans, query(L, R, rson, i));
	return ans;
}

int main() {
	// freopen("d.in", "r", stdin);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> arr[j][i];
	for (int i = 1; i <= m; i++) {
		build(i, roo);
	}
	int ans = 1;
	int a = 1, b = k;
	int t[6];
	while (a <= b) {
		int mid = a + b >> 1;
		bool flag = false;
		for (int i = 1; i + mid <= n + 1; i++) {
			int tt = 0;
			for (int j = 1; j <= m; j++) {
				t[j] = query(i, i + mid - 1, roo, j);
				tt += t[j];
			}
			if (tt <= k) {
				flag = true;
				break;
			}
		}
		if (flag) {
			a = mid + 1; ans = mid;
			for (int i = 1; i <= m; i++) res[i] = t[i];
		}
		else b = mid - 1;
	}
	for (int i = 1; i <= m; i++) {
		if (i > 1) cout << " ";
		cout << res[i];
	}
	return 0;
}
