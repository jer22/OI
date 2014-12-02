#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

int n, k;
int arr[MAXN];

/**
	是否可以取k个数使相邻之差不超过m
*/
bool canReach(int m) {
	// 已经取了cnt个数
	int cnt = 0;
	// 目前该取的数
	int minPoint = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] >= minPoint) {
			cnt++;
			minPoint = arr[i] + m;
		}
	}
	return cnt >= k;
}

int main() {
	freopen("1316.in", "r", stdin);
	scanf("%d %d", &n, &k);
	int a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + n);
	a = 1;
	b = arr[n - 1] - arr[0];
	while (a < b) {
		printf("%d %d\n", a, b);
		int c = ((a + b) >> 1) + 1;
		if (canReach(c)) {
			a = c;
		} else {
			b = c - 1;
		}
	}

	printf("%d\n", a);
	return 0;
}
