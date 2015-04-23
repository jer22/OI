#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define p(i, j) (((i) - 1) * m + (j))
#define getx(i) (((i - 1) / m) + 1)
#define gety(i) (((i - 1) % m) + 1)

using namespace std;

int n, m, k;
char g[35][35];
int dist[1005][1005];
int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
bool vis[1005];

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

void spfa(int s) {
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[s][s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		int x = getx(cur);
		int y = gety(cur);
		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0];
			int ny = y + dir[i][1];
			if (!check(nx, ny)) continue;
			int nex = p(nx, ny);
			int v = 0;
			if (g[nx][ny] == '1') v = 1;
			if (dist[s][cur] + v > k) continue;
			if (dist[s][cur] + v < dist[s][nex]) {
				dist[s][nex] = dist[s][cur] + v;
				if (!vis[nex]) {
					vis[nex] = 1;
					q.push(nex);
				}
			}
		}
		vis[cur] = 0;
	}
}

double getdist(int a, int b) {
	int ax = getx(a), ay = gety(a);
	int bx = getx(b), by = gety(b);
	return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
}

int main() {
	freopen("1295.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		scanf("%s", g[i] + 1);
	memset(dist, 0x3f, sizeof(dist));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (g[i][j] == '0') spfa(p(i, j));
		}
	}
	double ans = 0;
	for (int i = 1; i <= p(n, m); i++) {
		for (int j = 1; j <= p(n, m); j++) {
			if (dist[i][j] == INF) continue;
			ans = max(ans, getdist(i, j));
		}
	}
	printf("%.6lf\n", sqrt(ans));

	return 0;
}
