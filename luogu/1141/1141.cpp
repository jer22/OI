#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>

#define MAXN 1010

using namespace std;

int n, m;
int maxCnt = 1;
int color = 1;
int arr[MAXN][MAXN];
int re[MAXN][MAXN];
vector<int> q[2];
map<int, int> cnt;

void bfs(int a, int b) {

	q[0].clear();
	q[1].clear();
	q[0].push_back(a);
	q[1].push_back(b);
	int x, y;
	for (int i = 0; i < q[1].size(); i++) {
		x = q[0][i];
		y = q[1][i];
		
		re[x][y] = color;
		if (x < n && !re[x + 1][y] && (arr[x][y] ^ arr[x + 1][y])) {
			if (!re[x + 1][y])
				maxCnt++;
			re[x + 1][y] = color;
			q[0].push_back(x + 1);
			q[1].push_back(y);
		}
		if (x > 1 && !re[x - 1][y] && (arr[x][y] ^ arr[x - 1][y])) {
			if (!re[x - 1][y])
				maxCnt++;
			re[x - 1][y] = color;
			q[0].push_back(x - 1);
			q[1].push_back(y);
		}
		if (y > 1 && !re[x][y - 1] && (arr[x][y] ^ arr[x][y - 1])) {
			if (!re[x][y - 1])
				maxCnt++;
			re[x][y - 1] = color;
			q[0].push_back(x);
			q[1].push_back(y - 1);
		}
		if (y < n && !re[x][y + 1] && (arr[x][y] ^ arr[x][y + 1])) {
			if (!re[x][y + 1])
				maxCnt++;
			re[x][y + 1] = color;
			q[0].push_back(x);
			q[1].push_back(y + 1);
		}
	}
}

int main() {
	freopen("1141.in", "r", stdin);
	memset(arr, 0, sizeof(arr));
	memset(re, 0, sizeof(re));
	scanf("%d %d\n", &n, &m);
	string s;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		for (int j = 0; j < n; j++) {
			arr[i][j + 1] = s[j] - '0';
		}
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		maxCnt = 1;
		scanf("%d %d", &a, &b);
		if (re[a][b]) {
			maxCnt = cnt[re[a][b]];
		} else {
			re[a][b] = color;
			bfs(a, b);
			cnt[color] = maxCnt;
			color++;
		}

		// for (int j = 1; j <= n; j++) {
		// 	for (int k = 1; k <= n; k++) {
		// 		printf("%d ", re[j][k]);
		// 	}
		// 	printf("\n");
		// }
		printf("%d\n", maxCnt);
	}

	return 0;
}
