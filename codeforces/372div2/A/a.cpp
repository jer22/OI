#include <bits/stdc++.h>

using namespace std;

int n, c;
int arr[100005];
int main() {
	freopen("a.in", "r", stdin);
	cin >> n >> c;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	sort(arr + 1, arr + n + 1);
	int ans = 1;
	for (int i = 2; i <= n; i++) {
		if (arr[i] - arr[i - 1] <= c) ans++;
		else ans = 1;
	}
	cout << ans << endl;


	return 0;
}
