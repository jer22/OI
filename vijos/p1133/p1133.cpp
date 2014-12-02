#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int v, n;
int arr[32];
int dp[20010];
int main() {
	freopen("input", "r", stdin);
	scanf("%d %d", &v, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = v; j >= arr[i]; j--) {
			dp[j] = max(dp[j - arr[i]] + arr[i], dp[j]);
		}
	}
	printf("%d\n", v - dp[v]);
	return 0;
}
