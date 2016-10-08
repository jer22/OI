#include <bits/stdc++.h>

using namespace std;

int n, m;
int arr[25][25];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> arr[i][j];
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = 1; j <= m; j++) {
			if (arr[i][j] != j) cnt++;
		}
		if (cnt > 2) flag = false;
		if (cnt > 4) {
			cout << "NO" << endl;
			return 0;
		}
	}
	if (flag) {
		cout << "YES" << endl;
		return 0;
	}
	flag = false;
	for (int a = 1; a <= m; a++) {
		for (int b = a + 1; b <= m; b++) {
			bool fff = true;
			for (int i = 1; i <= n; i++) {
				int cnt = 0;
				for (int j = 1; j <= m; j++) {
					if (j == a){
						if (arr[i][j] != b) cnt++;	
					} else if (j == b) {
						if (arr[i][j] != a) cnt++;
					} else {
						if (arr[i][j] != j) cnt++;
					}
				}
				if (cnt > 2) fff = false;
			}
			if (fff) {
				flag = true;
				break;
			}
		}
		if (flag) break;
	}
	if (flag) cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}
