#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[2005][2005], brr[2005][2005];
int main() {
	freopen("matrix.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &arr[i][j]), arr[i][j] += arr[i - 1][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &brr[i][j]), brr[i][j] += brr[i][j - 1];
	int x1, x2, y1, y2;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		int ans = 0;
		for (int j = 1; j <= n; j++)
			ans += (arr[x2][j] - arr[x1 - 1][j]) * (brr[j][y2] - brr[j][y1 - 1]);
		cout << ans << endl;
	}



	return 0;
}
