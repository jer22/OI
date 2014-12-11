#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define root 1, n, 1
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 5000 << 2;

int n;
int arr[MAXN];
int x[5010];
int t;
void pushUp(int rt) {
	arr[rt] = arr[rt << 1] + arr[rt << 1 | 1];
}

void insert(int p, int l, int r, int rt) {
	if (l == r) {
		arr[rt] = 1;
		return;
	}
	int m = (l + r) >> 1;
	if (p <= m) insert(p, lch);
	if (p > m) insert(p, rch);
	pushUp(rt);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		
		return arr[rt];
	}
	int m = (l + r) >> 1;
	int ans = 0;
	if (L <= m) ans += query(L, R, lch);
	if (R > m) ans += query(L, R, rch);
	pushUp(rt);
	return ans;
}

int main() {
	freopen("1394.in", "r", stdin);
	while (~scanf("%d", &n)) {
		memset(arr, 0, sizeof(arr));
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &t);
			x[i] = t;
			t++;
			ans += query(t + 1, n, root);
			insert(t, root);
		}
		int temp = ans;
		for (int i = 1; i < n; i++) {
			temp -= x[i];
			temp += n - 1 - x[i];
			ans = min(ans, temp);
		}
		cout << ans << endl;
	}


	return 0;
}
