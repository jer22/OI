#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[50];
int main() {
	freopen("coin.in", "r", stdin);
	freopen("coin.out", "w", stdout);
	scanf("%d", &n);
	if (!n) {
		printf("0\n");
		return 0;
	}
	arr[1] = arr[2] = 1;
	for (int i = 3; i < n; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	printf("%d\n", arr[n - 1]);
	return 0;
}
