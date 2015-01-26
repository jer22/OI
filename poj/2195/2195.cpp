#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Point{
	int x, y;
}man[105], house[105];

int n, m;
int mcnt, hcnt;
int edges[105][105];
int A[105], B[105];
int mat[105];
bool visA[105], visB[105];
int d;

void init() {
	for (int i = 1; i <= mcnt; i++)
		for (int j = 1; j <= hcnt; j++)
			edges[i][j] = abs(man[i].x - house[j].x) + abs(man[i].y - house[j].y);

	memset(A, 0x3f, sizeof(A));
	memset(B, 0, sizeof(B));
	for (int i = 1; i <= mcnt; i++)
		for (int j = 1; j <= hcnt; j++)
			A[i] = min(A[i], edges[i][j]);
}

bool dfs(int i) {
	visA[i] = 1;
	for (int j = 1; j <= hcnt; j++) {
		if (!visB[j] && edges[i][j]) {
			int t = edges[i][j] - A[i] - B[j];
			if (!t) {
				visB[j] = 1;
				if (!mat[j] || dfs(mat[j])) {
					mat[j] = i;
					return true;
				}
			} else d = min(d, t);
		}
	}
	return false;
}

int match() {
	memset(mat, 0, sizeof(mat));
	for (int i = 1; i <= mcnt; i++) {
		while (true) {
			memset(visA, 0, sizeof(visA));
			memset(visB, 0, sizeof(visB));
			d = INF;
			if (dfs(i)) break;
			for (int j = 1; j <= mcnt; j++) {
				if (visA[j]) A[j] += d;
				if (visB[j]) B[j] -= d;
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= hcnt; i++)
		ans += edges[mat[i]][i];
	return ans;
}

int main() {
	while (~scanf("%d %d", &n, &m) && n && m) {
		char c;
		mcnt = hcnt = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> c;
				if (c == 'm') {
					mcnt++;
					man[mcnt].x = i;
					man[mcnt].y = j;
				} else if (c == 'H') {
					hcnt++;
					house[hcnt].x = i;
					house[hcnt].y = j;
				}
			}
		}
		init();
		int ans = match();
		printf("%d\n", ans);
	}
	return 0;
}
