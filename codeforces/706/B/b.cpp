#include <bits/stdc++.h>

using namespace std;

int n, m;
int arr[100005];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	sort(arr + 1, arr + n + 1);
	cin >> m;
	int t;
	while (m--) {
		cin >> t;
		int ans = upper_bound(arr + 1, arr + n + 1, t) - arr - 1;
		cout << ans << endl;
	}

	return 0;
}
