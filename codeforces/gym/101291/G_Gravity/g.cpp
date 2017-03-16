#include <bits/stdc++.h>

using namespace std;

int n, m;
char arr[100][100];

void solve(int x, int y) {
	for (int i = x + 1; i <= n; i++) {
		if (arr[i][y] == '.') swap(arr[i][y], arr[i - 1][y]);
		else break;
	}
}

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", arr[i] + 1);
	for (int j = 1; j <= m; j++) {
		for (int i = n; i >= 1; i--) {
			if (arr[i][j] != 'o') continue;
			solve(i, j);
		}
	}
	for (int i = 1; i <= n; i++)
		cout << arr[i] + 1 << endl;
	return 0;
}
