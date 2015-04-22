#include <bits/stdc++.h>

using namespace std;

int n;
long long t;
long long pos[100005];
int main() {
	freopen("3893.in", "r", stdin);
	cin >> n >> t;
	long long a, b;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &a, &b);
		pos[i] = a + b * t;
	}
	int ans = 0;
	long long pre = LONG_LONG_MAX;
	for (int i = n - 1; i >= 0; i--) {
		if (pos[i] < pre) {
			ans++;
			pre = pos[i];
		}
	}
	cout << ans << endl;

	return 0;
}
