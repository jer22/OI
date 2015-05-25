#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int H;
int arr[1005][1005];
int ans[1005][1005];
int dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int main() {
	freopen("picture.in", "r", stdin);
	while (~scanf("%d", &H) && H) {
		int a, b;
		int n = 1, m = 1;
		while (~scanf("%d %d", &a, &b) && (a || b)) {
			for (int i = 0; i < b; i++) {
				if (m > H) m = 1, n++;
				arr[n][m++] = a;
			}
		}
		m = H;
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				for (int k = 0; k < 8; k++) {
					int ni = i + dir[k][0];
					int nj = j + dir[k][1];
					if (ni >= 1 && ni <= n && nj >= 1 && nj <= m)
						ans[i][j] = max(ans[i][j], abs(arr[i][j] - arr[ni][nj]));
				}
			}
		}
		cout << H << endl;
		a = ans[1][1];
		b = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (ans[i][j] != a) {
					cout << a << ' ' << b << endl;
					a = ans[i][j];
					b = 1;
				} else b++;
			}
		}
		cout << a << ' ' << b << endl;
		cout << "0 0" << endl;
	}
	cout << "0" << endl;
	return 0;
}
