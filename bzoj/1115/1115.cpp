#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n;
int arr[1005];
int main() {
	freopen("1115.in", "r", stdin);
	int x;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int sg = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
		}
		for (int i = n; i > 1; i -= 2)
			sg ^= arr[i] - arr[i - 1];
		if (n & 1) sg ^= arr[1];
		if (!sg) printf("NIE\n");
		else printf("TAK\n");
	}

	return 0;
}
