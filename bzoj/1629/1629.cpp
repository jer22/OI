#include <bits/stdc++.h>

using namespace std;

struct Node{
	long long w, s;
	bool operator < (const Node &n) const {
		return w + s < n.w + n.s;
	}
};

int n;
Node arr[50005];
int main() {
	freopen("1629.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld %lld", &arr[i].w, &arr[i].s);
	sort(arr, arr + n);
	long long sum = 0;
	long long ans = -0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		ans = max(ans, sum - arr[i].s);
		sum += arr[i].w;
	}
	cout << ans << endl;

	return 0;
}
