#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, tot;
int arr[MAXN], d[MAXN];
bool vis[MAXN];
bool check(int x) {
	if (x == n + 1) return false;
	int cnt = 0;
	int tt = tot;
	memset(vis, 0, sizeof(vis));
	for (int i = x; i >= 1; i--) {
		if (!arr[i]) continue;
		if (!vis[arr[i]]) {
			cnt++;
			vis[arr[i]] = 1;

			if (i - 1 - m + cnt < tt) {
				// cout << tot;
				return false;
			}
			tt -= d[arr[i]];
		}
	}
	if (cnt < m) return false;
	return true;
}

int main() {
	freopen("d.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		
		cin >> arr[i];
	for (int i = 1; i <= m; i++) {
		cin >> d[i];
		tot += d[i];
	}
	int l = 1, r = n + 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	// cout << check(9);
	if (l > n) l = -1;
	cout << l << endl;


	return 0;
}
