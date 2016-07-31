#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int a[105];
int cnt[105];
int vis[105];
int c[105];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
		sum += a[i];
	}
	sum /= (n >> 1);

	for (int i = 1; i <= n >> 1; i++) {
		int idx1 = 0, idx2 = 0;
		for (int j = 1; j <= n; j++) {
			if (vis[a[j]] >= cnt[a[j]]) continue;
			if (c[j]) continue;
			idx1 = j;
			vis[a[j]]++;
			c[idx1] = 1;
			break;
		}
		for (int j = idx1 + 1; j <= n; j++) {
			if (vis[a[j]] >= cnt[a[j]]) continue;
			if (a[j] != sum - a[idx1]) continue;
			if (c[j]) continue;
			vis[a[j]]++;
			idx2 = j;
			c[idx2] = 1;
			break;
		}
		cout << idx1 << ' ' << idx2 << endl;

	}



	return 0;
}
