#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

int n;
int arr[MAXN];
int cnt = 0;

int main() {
	freopen("1969.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 1; i <= n; i++) {
		if (arr[i] > arr[i -1]) {
			cnt += arr[i] - arr[i - 1];
		}
	}
	printf("%d\n", cnt);
	return 0;
}
