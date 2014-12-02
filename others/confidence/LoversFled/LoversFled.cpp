#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int point[510][2];
int main() {
	freopen("LoversFled.in", "r", stdin);
	freopen("LoversFled.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &point[i][0], &point[i][1]);
	}
	if (n == 1) {
		printf("1\n");
		return 0;
	}
	int ans = 0;
	int maxans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans = 0;
			if (i == j || point[i][0] > point[j][0]) continue;
			for (int k = 0; k < n; k++) {
				if (k == i || k == j) {
					ans++;
					continue;
				}
				double x1 = point[k][0] - point[i][0];
				double y1 = point[k][1] - point[i][1];
				double x2 = point[j][0] - point[k][0];
				double y2 = point[j][1] - point[k][1];
				if ((x1 * x2 > 0) || (y1 * y2 > 0))
					continue;
				if ((!x1 && !x2)) {
					ans++;
					continue;
				}
				double k1 = y1 / x1;
				double k2 = y2 / x2;
				if (k1 == k2)
					ans++;
			}
			maxans = max(maxans, ans);
		}
	}
	printf("%d\n", maxans);
	return 0;
}
