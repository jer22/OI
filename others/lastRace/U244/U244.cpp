#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int start[5020];
int end[5020];
int arr[10010];
int main() {
	freopen("U244.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &start[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &end[i]);
	for (int i = 1; i <= n; i++) {
		arr[i] = end[i] - start[i];
		if (arr[i] < 0)
			arr[i] += 9;
		arr[n + i] = arr[i];
	}
	int minminans = 0x3f3f3f3f;
	int minans = 0x3f3f3f3f;
	int ans = 0;
	for (int k = 1; k <= n; k++) {
		ans = 0;
		for (int i = k; i <= n + k - 1; i++) {
			if (arr[i] > arr[i - 1])
				ans += arr[i] - arr[i - 1];
		}
		minans = min(ans, minans);
	}
	for (int i = 1; i <= n << 1; i++) {
		arr[i] = 9 - arr[i] + 1;
	}
	for (int k = 1; k <= n; k++) {
		ans = 0;
		for (int i = k; i <= n + k - 1; i++) {
			if (arr[i] > arr[i - 1])
				ans += arr[i] - arr[i - 1];
		}
		minminans = min(ans, minminans);
	}
	minminans = min(minans, minminans);
	printf("%d\n", minminans);
	return 0;
}
