/*
ID:shijiey1
PROG:camelot
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define INF 0x3f3f3f3f

using namespace std;

int n, m;
int x[805];
int y[805];
int xk, yk;
int c = 0;
vector<int> edges[1005];
void addEdge(int x1, int y1, int x2, int y2) {
	if (x2 < 1 || y2 < 1 || x2 > n || y2 > m) return;
	edges[x1 * 31 + y1].push_back(x2 * 31 + y2);
}

int t;
int dist[1005][1005][2];
void spfa(int sx, int sy) {
	int done[2][1005];
	memset(done, 0, sizeof(done));
	queue<int> q;
	int s = sx * 31 + sy;

	for (int i = 0; i <= t; i++) {
		dist[s][i][0] = dist[s][i][1] = INF;
	}
	dist[s][s][0] = 0;
	dist[s][s][1] = max(abs(xk - sx), abs(yk - sy));
	done[0][s] = 1;
	done[1][s] = 1;
	q.push(s << 1);
	q.push((s << 1) + 1);

	while (!q.empty()) {
		int current = q.front();
		// if (sx == 1 && sy == 8)printf("%d %d\n", current / 2 / 31, (current / 2) % 31);
		int state = current & 1;
		current >>= 1;
		q.pop();
		done[state][current] = 0;
		if (state == 0)
		{
			int n_dis = max(abs(xk - current / 31),abs(yk - current % 31));
			if ( n_dis + dist[s][current][state] < dist[s][current][1])
			{
				dist[s][current][1] = n_dis + dist[s][current][state];
				if (done[1][current] == 0)
				{
					done[1][current] = 1;
					q.push((current << 1) + 1);
				}
			}
		}
		for (int i = 0; i < edges[current].size(); i++) {
			// if (sx == 1 && sy == 8) {
			// 	printf("%d ", edges[current][i]);
			// }
			int nex = edges[current][i];
			if (dist[s][current][state] + 1 < dist[s][nex][state]) {
				dist[s][nex][state] = dist[s][current][state] + 1;
				if (!done[state][nex]) {
					done[state][nex] = 1;
					q.push(nex * 2 + state);
				}
			}
		}
	}
}

int main() {
	freopen("camelot.in", "r", stdin);
	freopen("camelot.out", "w", stdout);
	scanf("%d %d", &n, &m);
	t = n * 31 + m;
	char a;
	int b;
	cin >> a >> b;
	xk = b;
	yk = a - 'A' + 1;
	while (cin >> a >> b) {
		y[c] = a - 'A' + 1;
		x[c++] = b;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			addEdge(i, j, i - 1, j - 2);
			addEdge(i, j, i - 1, j + 2);
			addEdge(i, j, i + 1, j - 2);
			addEdge(i, j, i + 1, j + 2);
			addEdge(i, j, i - 2, j - 1);
			addEdge(i, j, i - 2, j + 1);
			addEdge(i, j, i + 2, j - 1);
			addEdge(i, j, i + 2, j + 1);
		}
	}
	for (int i = 0; i < c; i++) {
		spfa(x[i], y[i]);
	}
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= m; j++) {
	// 		printf("%d ", dist[38][i * 31 + j][0]);
	// 	}
	// 	printf("\n");
	// }
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= m; j++) {
	// 		if (dist[32][i * 31 + j][0]) {
	// 			printf("%d %d %d\n", i, j, dist[32][i * 31 + j][1]);
	// 		}
	// 	}
	// }


	int best = INF;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int ans = 0;
			int k;
			for (k = 0; k < c; k++) {
				ans += dist[x[k] * 31 + y[k]][i * 31 + j][0];
				if (dist[x[k] * 31 + y[k]][i * 31 + j][0] == INF) break;
				// printf("%d ", dist[x[k] * 31 + y[k]][i * 31 + j][0]);
			}
			if (k != c) continue;
			// printf("%d\n", ans + max(abs(xk - i), abs(yk - j)));
			for (int k = 0; k < c; k++) {
				best = min(best, ans - dist[x[k] * 31 + y[k]][i * 31 + j][0] +  dist[x[k] * 31 + y[k]][i * 31 + j][1]);
			}
			best = min(best, ans + max(abs(xk - i), abs(yk - j)));
		}
	}
	if (best == INF) best = 0;
	printf("%d\n", best);
	return 0;
}
