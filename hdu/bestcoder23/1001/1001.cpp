#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int arr[1111];
int n;
int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(arr, 0, sizeof(arr));
		int sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			if (i % 2) sum += arr[i];
			else sum -= arr[i];
		}
		if (sum) {
			printf("No\n");
			continue;
		}
		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (arr[i] != arr[n - i - 1]) {
				printf("Yes\n");
				flag = false;
				break;
			}
		}
		if (flag) printf("No\n");
	}

	return 0;
}
