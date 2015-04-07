#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define P(x, y) (x) * m + (y)

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m;
int sx, sy, ex, ey;
int map[35][35];
int dir[8][2] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
vector<Edge> edges[1005];

bool check(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= m) return false;
	if (map[x][y] == 2) return false;
	return true;
}

int dist[1005];
int step[1005];
long long tot[1005];
bool vis[1005];

void spfa() {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(step, 0x3f, sizeof(step));
	int s = P(sx, sy);
	q.push(s);
	step[s] = 0;
	dist[s] = 0;
	tot[s] = 1;
	vis[s] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (dist[cur] + e.v == dist[e.to]) {
				if (step[cur] + 1 == step[e.to]) {
					tot[e.to] += tot[cur];
					if (!vis[e.to]) {
						vis[e.to] = 1;
						q.push(e.to);
					}
				}
				if (step[cur] + 1 < step[e.to]) {
					step[e.to] = step[cur] + 1;
					tot[e.to] += tot[cur];
					if (!vis[e.to]) {
						vis[e.to] = 1;
						q.push(e.to);
					}
				}
			}
			if (dist[cur] + e.v < dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
				step[e.to] = step[cur] + 1;
				tot[e.to] = tot[cur];
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
}

int main() {
	freopen("1632.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 3) sx = i, sy = j, map[i][j] = 0;
			if (map[i][j] == 4) ex = i, ey = j, map[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 2) continue;
			for (int k = 0; k < 8; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (!check(nx, ny)) continue;
				int v = !map[nx][ny];
				edges[P(i, j)].push_back(Edge(P(nx, ny), v));
			}
		}
	}
	spfa();
	int e = P(ex, ey);
	if (dist[e] == INF) {
		printf("-1\n");
		return 0;
	}
	printf("%d\n%d\n%lld\n", dist[e] - 1, step[e], tot[e]);

	return 0;
}
