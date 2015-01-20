#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
};

int T;
int n;
int tim[505];
int dist[505];
int mat[505];
int vis[505];
Point endPoint[505];
vector<int> edges[505];
// 两地的曼哈顿距离
int getDist(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) + abs(y2 - y1);
}

bool dfs(int k) {
	for (int i = 0; i < edges[k].size(); i++) {
		int j = edges[k][i];
		if (!vis[j]) {
			vis[j] = 1;
			if (!mat[j] || dfs(mat[j])) {
				mat[j] = k;
				return true;
			}
		}
	}
	return false;
}

int match() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int h, m;
		int x1, y1, x2, y2;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d:%d", &h, &m);
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			endPoint[i] = Point(x2, y2);	// 目的地
			tim[i] = h * 60 + m;	// 出发时间
			dist[i] = getDist(x1, y1, x2, y2); // 从出发地到目的地的距离
			for (int j = 1; j < i; j++) {
				if (dist[j] + getDist(endPoint[j].x, endPoint[j].y, x1, y1) + tim[j] < tim[i])
					edges[j].push_back(i);
			}
		}
		memset(mat, 0, sizeof(mat));
		int ans = n - match();
		printf("%d\n", ans);
	}
	return 0;
}
