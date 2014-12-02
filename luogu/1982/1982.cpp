#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 1000010

using namespace std;

int n, k;
int arr[MAXN];
long long sum[MAXN];
long long feature[MAXN];
long long point[MAXN];
long long ans = 0;
long long minnum = 0;

int main() {
	freopen("1982.in", "r", stdin);
	memset(sum, 0, sizeof(sum));
	memset(feature, 0, sizeof(feature));
	memset(point, 0, sizeof(point));
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
	}
	
	feature[1] = arr[1];
	ans = feature[1];
	point[1] = (feature[1]);
	point[2] = point[1] + feature[1];
	for (int i = 2; i <= n; i++) {
		minnum = min(minnum, sum[i - 1]);
		feature[i] = max(feature[i - 1], (sum[i] - minnum));
	}
	for (int i = 3; i <= n; i++) {
		point[i] = (point[i - 1] + max(feature[i - 1], 0ll)) % k;
	}

	ans = max(point[1] % k, point[n]);;
	cout << ans << endl;
	return 0;
}
