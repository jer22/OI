#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 10005;

int n, m, h, idx;

struct Node {
	int x, y;
	Node() {}
	Node(int a, int b) : x(a), y(b) {}
	bool operator < (const Node &n) const {
		if (x != n.x) return x < n.x;
		return y < n.y;
	}
}arr[10005];
int sum[10005];
int main() {
	freopen("1635.in", "r", stdin);
	scanf("%d %d %d %d", &n, &idx, &h, &m);
	int a, b;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		if (a > b) swap(a, b);
		arr[i] = Node(a, b);
	}
	sort(arr + 1, arr + m + 1);
	arr[0].x = -1;
	for (int i = 1; i <= m; i++) {
		if (arr[i].x == arr[i - 1].x && arr[i].y == arr[i - 1].y) continue;
		sum[arr[i].x + 1]--;
		sum[arr[i].y]++;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += sum[i];
		cout << ans + h << endl;
	}


	return 0;
}
