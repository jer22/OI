#include <bits/stdc++.h>

using namespace std;

int n, k;
int arr[505];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	int ans = 0;
	for (int i = 2; i <= n; i++) {
		if (arr[i] + arr[i - 1] < k) {
			ans += k - arr[i] - arr[i - 1];
			arr[i] += k - arr[i] - arr[i - 1];
		}
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++) {
		if (i != 1) cout << ' ';
		cout << arr[i];
	}
	cout << endl;

	return 0;
}
