#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Point{
	int l, r, y;
	bool operator < (const Point &p) const {
		return y > p.y;
	}
};

int x, y;
int n;
Point arr[110];
int ans = 0;
int main() {
	freopen("fall.in", "r", stdin);
	freopen("fall.out", "w", stdout);
	scanf("%d %d", &x, &y);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &arr[i].y, &arr[i].l, &arr[i].r);
	}
	ans = y;
	sort(arr, arr + n);
	for (int i = 0; i < n; i++) {
		if (arr[i].y > y) continue;
		if (arr[i].l <= x && arr[i].r >= x) {
			x = arr[i].r;
			ans += 5;
		}
	}
	printf("%d\n", ans);
	return 0;
}
