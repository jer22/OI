#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 10010

using namespace std;

int n;
int arr[MAXN];
int num = 0;
int cnt = 0;
int main() {
	freopen("1031.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		num += arr[i];
	}
	num /= n;
	for (int i = 0; i < n; i++) {
		arr[i] -= num;
	}
	for (int i = 0; i < n - 1; i++) {
		if (arr[i]) {
			arr[i + 1] += arr[i];
			arr[i] = 0;
			cnt++;
		}
	}
	printf("%d\n", cnt);

	return 0;
}
