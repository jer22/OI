#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m;
int map[35][35];
vector<Edge> edges[1005];
int sx, sy, ex, ey;
int dir[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

bool check(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= m) return false;
	if (map[x][y] == 2) return false;
	return true;
}

int dist[1005];
long long ans[1005];
bool vis[1005];
void bfs() {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(ans, 0, sizeof(ans));
	memset(vis, 0, sizeof(vis));
	int s = sx * m + sy;
	q.push(s);
	dist[s] = 0;
	ans[s] = 1;
	vis[s] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (dist[cur] + e.v == dist[e.to]) {
				ans[e.to] += ans[cur];
				if (!vis[e.to]) {
					if (e.to != ex * m + ey) {
						vis[e.to] = 1;
						q.push(e.to);
					}
				}
			}
			if (dist[cur] + e.v < dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
				ans[e.to] = ans[cur];
				if (!vis[e.to]) {
					if (e.to != ex * m + ey) {
						vis[e.to] = 1;
						q.push(e.to);
					}
				}
			}
		}
	}
}

int tmp[1005], tot = 0;
int vis2[1005];
int used[1005][1005];
void dfs(int x, int y) {
	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (!check(nx, ny)) continue;
		if (!map[nx][ny] && !vis2[nx * m + ny]) {
			vis2[nx * m + ny] = 1;
			tmp[tot++] = nx * m + ny;
		}
		if (map[nx][ny] == 1 && !vis[nx * m + ny]) {
			vis[nx * m + ny] = 1;
			dfs(nx, ny);
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	int t;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 3) {
				sx = i;
				sy = j;
				map[i][j] = 0;
			}
			if (map[i][j] == 4) {
				ex = i;
				ey = j;
				map[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j]) continue;
			for (int k = 0; k < 8; k++) {
				int nx = i + dir[k][0];
				int ny = j + dir[k][1];
				if (check(nx, ny) && !map[nx][ny])
					edges[i * m + j].push_back(Edge(nx * m + ny, 1));
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 1 && !vis[i * m + j]) {
				tot = 0;
				memset(vis2, 0, sizeof(vis2));
				vis[i * j + 1] = 1;
				dfs(i, j);
				for (int k = 0; k < tot; k++) {
					for (int l = k + 1; l < tot; l++) {
						if (!used[tmp[k]][tmp[l]]) {
							used[tmp[k]][tmp[l]] = used[tmp[l]][tmp[k]] = 1;
							edges[tmp[k]].push_back(Edge(tmp[l], 1));
							edges[tmp[l]].push_back(Edge(tmp[k], 1));
						}
					}
				}
			}
		}
	}
	bfs();
	if (dist[ex * m + ey] == 0x3f3f3f3f) {
		printf("-1\n");
		return 0;
	}
	printf("%d\n%lld\n", dist[ex * m + ey] - 1, ans[ex * m + ey]);
	return 0;
}
