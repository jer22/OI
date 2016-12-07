#include <bits/stdc++.h>

using namespace std;

int n, x;
int arr[100005];
map<int, int> cnt;
int main() {
	// freopen("b.in", "r", stdin);
	scanf("%d %d", &n, &x);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		ans += cnt[x ^ arr[i]];
		cnt[arr[i]]++;
	}
	cout << ans << endl;

	return 0;
}
