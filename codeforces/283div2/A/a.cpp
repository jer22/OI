#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[111];
int dif[111];
int b;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	int t = 0x3f3f3f3f;
	int idx;
	for (int i = 0; i < n - 2; i++) {
		b = arr[i + 2] - arr[i];
		if (b < t) {
			t = b;
			idx = i;
		}
	}
	arr[idx + 1] = arr[idx];
	int ans = 0;
	for (int i = 0; i < n - 1; i++) {
		ans = max(ans, arr[i + 1] - arr[i]);
	}
	printf("%d\n", ans);
	return 0;
}
