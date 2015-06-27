#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, l;
int arr[1005];
int main() {
	scanf("%d %d", &n, &l);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	arr[n + 1] = l;
	sort(arr, arr + n + 1);
	int ans = 0;
	for (int i = 1; i < n; i++) {
		ans = max(ans, arr[i + 1] - arr[i]);
	}
	ans = max(ans, arr[1] * 2);
	ans = max(ans, (l - arr[n]) * 2);
	double d = (double)ans / 2;
	printf("%.10lf\n", d);

	return 0;
}
