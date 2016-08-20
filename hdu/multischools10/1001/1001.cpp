#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n, m;
int arr[100005];

int getans(int a, int b, int c, int d, int mid, int tot) {
	if (b < c) {
		if (a + mid - 1 <= b) return arr[a + mid - 1];
		else return arr[c + a + mid - 1 - b - 1];
	} else {
		if (b > d) swap(b, d);
		if (a + mid - 1 < c) return arr[a + mid - 1];
		if (d - (tot - mid + 1) + 1 > b) {
			return arr[d - (tot - mid + 1) + 1];
		}
		mid -= c - a;
		mid = mid - 1 >> 1;

		return arr[c + mid];
	}
}

int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		int a, b, c, d;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			if (a > c) {
				swap(a, c);
				swap(b, d);
			}
			int l1 = b - a + 1;
			int l2 = d - c + 1;

			int mid = (l1 + l2 >> 1) + 1;
			if ((l1 + l2) & 1) {
				int ans = getans(a, b, c, d, mid, l1 + l2);
				printf("%.1lf\n", double(ans));
			} else {
				int a1 = getans(a, b, c, d, mid - 1, l1 + l2);
				int a2 = getans(a, b, c, d, mid, l1 + l2);
				printf("%.1lf\n", double(a1 + a2) / 2.0);
			}

		}
	}



	return 0;
}
