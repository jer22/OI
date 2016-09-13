#include <bits/stdc++.h>

using namespace std;

int n;
int arr[100005];
int main() {
	freopen("a.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	int ans = 0;
	int mx = 0;
	for (int i = 1; i <= n; i++) {
		if (arr[i] > arr[i - 1]) {
			ans++;
		} else {
			mx = max(ans, mx);
			ans = 1;
		}
	}
	mx = max(mx, ans);
	cout << mx << endl;


	return 0;
}
