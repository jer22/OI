#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAXN  500010

using namespace std;

int n, k;
long long arr[MAXN];
long long temp[MAXN];

int main() {
	freopen("2263.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	long long ans = 1000000000010;
	if (k == 2) {
		for (int i = 1; i < n; i++) {
			long long t = abs(arr[i + 1] - arr[i]);
			ans = min(t, ans);
		}
		cout << ans << endl;
		return 0;
	}
	
	for (int i = 1; i <= n - k + 1; i++) {
		long long now = 0;
		memset(temp, 0, sizeof(temp));
		for (int j = 0; j < k; j++) {
			temp[j] = arr[i + j];
		}
		sort(temp, temp + k);
		long long mid = temp[k >> 1];
		for (int j = 0; j < k; j++) {
			now += abs(temp[j] - mid);
		}
		ans = min(ans, now);
	}
	cout << ans << endl;
	return 0;
}
