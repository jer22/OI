#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int step;
	int x1, y1, x2, y2;
	int gx1, gy1, gx2, gy2;
	Node() {}
	Node(int a, int b, int c, int d, int e, int f1, int f2, int f3, int f4)
		: x1(a), y1(b), x2(c), y2(d), step(e), gx1(f1), gy1(f2), gx2(f3), gy2(f4) {}
};

int T;
int n, m;
int sx1, sy1, sx2, sy2;
int Go[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int arr[24][24];
int hole[24][24];
int vis[24][24][24][24];
int bfs() {
	memset(vis, 0, sizeof(vis));
	vis[sx1][sy1][sx2][sy2] = 1;
	queue<Node> q;
	Node e = Node(sx1, sy1, sx2, sy2, 0, -1, -1, -1, -1);
	q.push(e);
	while (!q.empty()) {
		e = q.front();
		q.pop();
		// 两球都已经进洞就返回步数
		if (e.gx1 != -1 && e.gx2 != -1) return e.step;
		for (int i = 0; i < 4; i++) {
			// 两个球前方都有墙就不考虑
			if (arr[e.x1 + Go[i][0]][e.y1 + Go[i][1]] && arr[e.x2 + Go[i][0]][e.y2 + Go[i][1]]) continue;
			// 前进一步后两球的坐标
			int nx1, ny1, nx2, ny2;
			// 前方有墙或该球已经进洞，坐标不变
			if (arr[e.x1 + Go[i][0]][e.y1 + Go[i][1]] || e.gx1 != -1) {
				nx1 = e.x1;
				ny1 = e.y1;
			}
			// 否则向前一步
			else {
				nx1 = e.x1 + Go[i][0];
				ny1 = e.y1 + Go[i][1];
			}
			// 同理
			if (arr[e.x2 + Go[i][0]][e.y2 + Go[i][1]] || e.gx2 != -1) {
				nx2 = e.x2;
				ny2 = e.y2;
			} else {
				nx2 = e.x2 + Go[i][0];
				ny2 = e.y2 + Go[i][1];
			}
			// 该状态已经处理过直接continue
			if (vis[nx1][ny1][nx2][ny2]) continue;
			/*
				可能会出现两个球的坐标重合的情况，如：	
				BB*
				此时向右一步，右边的球不动，而左边的球向右一步，此时两球重和。
				这种情况直接continue。
				但也有可能其中一球已经进洞，此时它便可以看作空地，即使坐标重合也无所谓。
			*/
			if ((nx1 == nx2 && ny1 == ny2) && e.gx1 == -1 && e.gx2 == -1) continue;
			vis[nx1][ny1][nx2][ny2] = 1;
			int ngx1 = e.gx1, ngy1 = e.gy1, ngx2 = e.gx2, ngy2 = e.gy2;
			// 该球的坐标上有洞，且另一球没有进此洞，则使该球进洞
			if (hole[nx1][ny1] && (e.gx2 != nx1 || e.gy2 != ny1)) {
				ngx1 = nx1;
				ngy1 = ny1;
			}
			if (hole[nx2][ny2] && (e.gx1 != nx2 || e.gy1 != ny2)) {
				ngx2 = nx2;
				ngy2 = ny2;
			}
			Node nex = Node(nx1, ny1, nx2, ny2, e.step + 1, ngx1, ngy1, ngx2, ngy2);
			q.push(nex);
		}
	}
	return 0;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(arr, 0, sizeof(arr));
		memset(hole, 0, sizeof(hole));
		scanf("%d %d\n", &n, &m);
		char c;
		sx1 = sy1 = sx2 = sy2 = -1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%c", &c);
				if (c == '*') arr[i][j] = 1;
				else if (c == 'B') {
					if (sx1 == -1) sx1 = i, sy1 = j;
					else sx2 = i, sy2 = j;
				} else if (c == 'H') hole[i][j] = 1;
			}
			getchar();
		}
		int ans = bfs();
		if (ans) printf("%d\n", ans);
		else printf("Sorry , sir , my poor program fails to get an answer.\n");
	}
	return 0;
}
