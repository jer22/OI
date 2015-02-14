#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[12][12];

int main() {
	freopen("a.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		memset(arr, 0, sizeof(arr));
		for (int i = 2; i <= n; i++)
			arr[1][i] = 1;
		for (int i = 2; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= n; k++) {
					if (k == j) continue;
					arr[i][j] += arr[i - 1][k];
				}
			}
		}
		cout << arr[m][1] << endl;
	}
	return 0;
}
