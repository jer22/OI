#include <bits/stdc++.h>

using namespace std;

int n, k;
int ans;
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> k;
	ans = (n * n + 1) >> 1;
	int cnt = 0;
	bool flag = false;
	if (k > ans) cout << "NO" << endl;
	else {
		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (cnt == k) flag = true;
				if (!((i + j) & 1) && !flag) {
					cnt++;
					cout << 'L';
				} else cout << 'S';
			}
			cout << endl;
		}
	}


	return 0;
}
