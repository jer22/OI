/*
ID:shijiey1
PROG:sort3
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[1010], brr[1010];
int g[5][5];
int ans = 0;
int main() {
	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		brr[i] = arr[i];
	}
	sort(brr, brr + n);
	for (int i = 0; i < n; i++) {
		g[arr[i]][brr[i]]++;
	}
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			if (i != j) {
				int minn = min(g[i][j], g[j][i]);
				ans += minn;
				g[i][j] -= minn;
				g[j][i] -= minn;
			}
		}
	}
	while (g[1][2] && g[2][3] && g[3][1]) {
		ans += 2;
		g[1][2]--;
		g[2][3]--;
		g[3][1]--;
	}
	while (g[1][3] && g[3][2] && g[2][1]) {
		ans += 2;
		g[1][3]--;
		g[2][1]--;
		g[3][2]--;
	}
	printf("%d\n", ans);
	return 0;
}
