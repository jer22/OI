#include <bits/stdc++.h>

using namespace std;

int n;
int arr[55][55];

void dfs1(int i, int j, int num) {
	if (num == n * n + 1) return;
	if (i > n) i = 1;
	if (arr[i][j]) dfs1(i + 1, j, num);
	arr[i][j] = num;
	int ni = i - 1, nj = j + 1;
	if (ni < 1) ni = n;
	if (nj > n) nj = 1;
	if (arr[ni][nj]) {
		ni = i + 1, nj = j;
	}
	dfs1(ni, nj, num + 1);
}

int main() {
	freopen("c.in", "r", stdin);
	cin >> n;
	if (n & 1) {
		dfs1(1, n + 1 >> 1, 1);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (j > 1) cout << ' ';
				cout << arr[i][j];
			}
			cout << endl;
		}
	}



	return 0;
}
