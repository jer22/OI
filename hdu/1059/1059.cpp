#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int arr[200];
int dp[150000];
int main() {
	freopen("1059.in", "r", stdin);
	int T = 0;
	int t[6];
	while (scanf("%d %d %d %d %d %d", &t[0], &t[1], &t[2], &t[3], &t[4], &t[5])) {
		T++;
		if (!(t[0] | t[1] | t[2] | t[3] | t[4] | t[5])) break;
		int n = 0;
		int sum = 0;
		for (int i = 0; i < 6; i++) {
			if (!t[i]) continue;
			int base = 1;
			while (t[i] - base > 0) {
				arr[n++] = base * (i + 1);
				t[i] -= base;
				base <<= 1;
				sum += arr[n - 1];
			}
			arr[n++] = t[i] * (i + 1);
			sum += arr[n - 1];
		}
		if (sum % 2) {
			printf("Collection #%d:\nCan't be divided.\n", T);
			printf("\n");
			continue;
		}
		sum >>= 1;
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; i++) {
			for (int j = sum; j >= arr[i]; j--) {
				dp[j] = max(dp[j], dp[j - arr[i]] + arr[i]);
			}
		}
		if (dp[sum] == sum) {
			printf("Collection #%d:\nCan be divided.\n", T);
			printf("\n");
		} else {
			printf("Collection #%d:\nCan't be divided.\n", T);
			printf("\n");
		}
	}

	return 0;
}
