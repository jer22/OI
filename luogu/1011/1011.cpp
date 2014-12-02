#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int a, n, m, x;
int arr[25];
int ans = 0;
int main() {
	freopen("1011.in", "r", stdin);
	scanf("%d %d %d %d", &a, &n, &m, &x);
	if (x == 1 || x == 2) {
		ans = a;
	} else if (x == 3) {
		ans = a << 1;
	} else {
		arr[1] = 1;
		arr[2] = 1;
		for (int i = 3; i <= n; i++) {
			arr[i] = arr[i - 1] + arr[i - 2];
		}
		int totala = 2;
		int totals = 0;
		for (int i = 4; i < n; i++) {
			totala += arr[i - 4];
			totals += arr[i - 3];
		}
		int second = (m - totala * a) / totals;
		totala = 2;
		totals = 0;
		for (int i = 4; i <= x; i++) {
			totala += arr[i - 4];
			totals += arr[i - 3];
		}
		ans = totala * a + totals * second;
	}
	
	printf("%d\n", ans);
	return 0;
}
