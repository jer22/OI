#include <bits/stdc++.h>

using namespace std;

int n;
int arr[100005];
map<int, int> vis;

int main() {
	freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		if (!vis[arr[i]]) vis[arr[i]] = 1;
		else vis[arr[i]]++;
	}
	// cout << (1 << 30);
	long long ans = 0;
	for (int num = 2; num <= 1 << 30 && num > 0; num <<= 1) {
		for (int i = 1; i <= n; i++) {
			int a = arr[i];
			if (!vis[num - a]) continue;
			int b = num - a;
			int t = vis[b];
			if (a == b) ans += (long long)(t - 1);
			else ans += t;
		}
	}
	cout << ans / 2 << endl;

	return 0;
}
