#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int n, k;
int maxx = 0, maxy = 0;
int minx = INF, miny = INF;
int point[55][2];
int area[55][55];
int borderX[55][55][2];
int borderY[55][55][2];
int getMaxx(int a, int b) {
	if (borderX[a][b][0]) {
		return borderX[a][b][0];
	}
	int re = 0;
	for (int i = a; i <= b; i++) {
		re = max(re, point[i][0]);
		borderX[a][b][0] = re;
	}
	return re;
}

int getMinx(int a, int b) {
	if (borderX[a][b][1]) {
		return borderX[a][b][1];
	}
	int re = INF;
	for (int i = a; i <= b; i++) {
		re = min(re, point[i][0]);
		borderX[a][b][1] = re;
	}
	return re;
}

int getMaxy(int a, int b) {
	if (borderY[a][b][0]) {
		return borderY[a][b][0];
	}
	int re = 0;
	for (int i = a; i <= b; i++) {
		re = max(re, point[i][1]);
		borderY[a][b][0] = re;
	}
	return re;
}

int getMiny(int a, int b) {
	if (borderY[a][b][1]) {
		return borderY[a][b][1];
	}
	int re = INF;
	for (int i = a; i <= b; i++) {
		re = min(re, point[i][1]);
		borderY[a][b][1] = re;
	}
	return re;
}

int main() {
	freopen("1034.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &point[i][0], &point[i][1]);

	}
	if (k == 1) {
		printf("%d", (getMaxx(0, n - 1) - getMinx(0, n - 1)) * (getMaxy(0, n - 1) - getMiny(0, n - 1)));
		return 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			area[i][j] = (getMaxx(i, j) - getMinx(i, j)) * (getMaxy(i, j) - getMiny(i, j));
		}
	}
	int ans = INF;
	if (k == 2) {
		for (int i = 0; i < n - 1; i++) {
			ans = min(ans, area[0][i] + area[i + 1][n - 1]);
		}
		
	}
	if (k == 3) {
		for (int i = 0; i < n - 2; i++) {
			for (int j = i + 1; j < n - 1; j++) {
				ans = min(ans, area[0][i] + area[i + 1][j] + area[j + 1][n - 1]);
			}
		}
	}
	if (k == 4) {
		for (int i = 0; i < n - 3; i++) {
			for (int j = i + 1; j < n - 2; j++) {
				for (int k = j + 1; k < n - 1; k++) {
					ans = min(ans, area[0][i] + area[i + 1][j] + area[j + 1][k] + area[k + 1][n - 1]);
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
