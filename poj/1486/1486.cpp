#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Rec{
	int x1, y1, x2, y2;
};

int n;
int edges[105][105];
Rec recs[105];
int mat[105];
int vis[105];

bool dfs(int k) {
	for (int i = 1; i <= n; i++) {
		if (edges[k][i] && !vis[i]) {
			vis[i] = 1;
			if (!mat[i] || dfs(mat[i])) {
				mat[i] = k;
				return true;
			}
		}
	}
	return false;
}

void match() {
	memset(mat, 0, sizeof(mat));
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		dfs(i);
	}
}

int main() {
	freopen("1486.in", "r", stdin);
	int cas = 1;
	while (~scanf("%d", &n) && n) {
		memset(edges, 0, sizeof(edges));
		for (int i = 1; i <= n; i++)
			scanf("%d %d %d %d", &recs[i].x1, &recs[i].x2, &recs[i].y1, &recs[i].y2);
		int x, y;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &x, &y);
			for (int j = 1; j <= n; j++) {
				if (recs[j].x1 < x && recs[j].x2 > x && recs[j].y1 < y && recs[j].y2 > y)
					edges[i][j] = 1;
			}
		}
		match();
		bool flag = false;
		printf("Heap %d\n", cas++);
		for (int i = 1; i <= n; i++) {
			if (!mat[i]) continue;
			int point = mat[i];
			mat[i] = 0;
			edges[point][i] = 0;
			memset(vis, 0, sizeof(vis));
			if (!dfs(point)) {
				if (flag) printf(" ");
				else flag = true;
				printf("(%c,%d)", 'A' + i - 1, point);
				mat[i] = point;
			}
			edges[point][i] = 1;
		}
		if (!flag) printf("none");
		printf("\n\n");
	}


	return 0;
}
