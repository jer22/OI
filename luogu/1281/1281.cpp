#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, k;
int arr[510];
int ans[510][2];

bool canWrite(int m) {
	int cnt = 0;
	int total = 0;
	for (int i = 1; i <= n; i++) {
		total += arr[i];
		if (total > m) {
			total = arr[i];
			cnt++;
		}
	}
	if (total) cnt++;
	return cnt <= k;
}

int main() {
	freopen("1281.in", "r", stdin);
	scanf("%d %d", &n, &k);
	int a = 0;
	int b = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		b += arr[i];
		a = max(a, arr[i]);
	}
	while (a < b) {
		int c = (a + b) >> 1;
		if (canWrite(c)) {
			b = c;
		}else {
			a = c + 1;
		}
	}
	int total = 0;
	int j = k;
	ans[j][1] = n;
	ans[1][0] = 1;
	for (int i = n; i >= 1; i--) {
		total += arr[i];
		if (total > a) {
			total = arr[i];
			ans[j][0] = i + 1;
			j--;
			ans[j][1] = i;
		}
	}
	for (int i = 1; i <= k; i++) {
		printf("%d %d\n", ans[i][0], ans[i][1]);
	}
	return 0;
}
