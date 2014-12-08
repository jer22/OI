/*
ID:shijiey1
PROG:sort3
LANG:C++
*/

/*
用arr记录初始数列，brr记录排好序的数列。
对于一个位置i，原来是a而现在是b，则从a到b连一条边（g[a][b]++）。
如果g[x][y]与g[y][x]都有边，则交换次数加1,g[x][y]与g[y][x]各减1。
为什么呢?
因为如果一个位置原来是x现在是y，另一个位置原来是y现在是x，则我们可以用一次来交换他们使两个位置上都变成正确的数字。
同理如果g里有环，即g[x][y],g[y][z], g[z][x]都不为零，则可以用两次来交换他们。
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
