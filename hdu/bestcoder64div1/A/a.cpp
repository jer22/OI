#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 10007;

int n;
int arr[100005], brr[100005];
int dp[100005];
int sum[100005];

int f(int x) {
	return (1890 * x + 143) % MOD;
}

int main() {
	freopen("a.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			sum += arr[i];
			brr[i] = f(arr[i]) - arr[i];
		}
		int mx = 0;
		int tmp = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			tmp += brr[i];;
			mx = max(mx, tmp);
			tmp = max(tmp, 0);
		}
		cout << sum + mx << endl;
		
	}

	return 0;
}
