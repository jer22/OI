#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n;
int arr[20005];
int main() {
	freopen("k.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		sort(arr, arr + n);
		int ans = 0;
		for (int i = n - 3; i >= 0; i -= 3) {
			ans += arr[i];
		}
		printf("%d\n", ans);
	}


	return 0;
}
