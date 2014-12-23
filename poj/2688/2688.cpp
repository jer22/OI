#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int n, m;
int cnt;
int vertex[12];
char map[22][22];
vector<int> edges[444];
void addEdge(int from, int to) {
	edges[from].push_back(to);
}

int dist[22][444];
void spfa(int s) {
	bool vis[444];
	memset(vis, 0, sizeof(vis));
	vis[vertex[s]] = 1;
	dist[s][vertex[s]] = 0;
	queue<int> q;
	q.push(vertex[s]);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			int e = edges[cur][i];
			if (dist[s][cur] + 1 < dist[s][e]) {
				dist[s][e] = dist[s][cur] + 1;
				if (!vis[e]) {
					vis[e] = 1;
					q.push(e);
				}
			}
		}
	}
}

int ans;
bool vis[22];
void dfs(int step, int v, int cur) {
	if (cur > ans) return;
	if (step == cnt) {
		ans = cur;
		return;
	}
	for (int i = 1; i < cnt; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			dfs(step + 1, i, cur + dist[v][vertex[i]]);
			vis[i] = 0;
		}
	}
}

int main() {
	while (~scanf("%d %d", &m, &n) && n && m) {
		memset(vertex, -1, sizeof(vertex));
		memset(dist, 0x3f, sizeof(dist));
		memset(map, 0, sizeof(map));
		for (int i = 0; i < n * m + m; i++) {edges[i].clear();}
		for (int i = 0; i < n; i++)
			scanf("%s", map[i]);
		cnt = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 'o') vertex[0] = i * m + j;
				if (map[i][j] == '*') vertex[cnt++] = i * m + j;
				if (map[i][j] != 'x') {
					if (i > 0 && map[i - 1][j] != 'x') addEdge(i * m + j, (i - 1) * m + j);
					if (i < n - 1 && map[i + 1][j] != 'x') addEdge(i * m + j, (i + 1) * m + j);
					if (j > 0 && map[i][j - 1] != 'x') addEdge(i * m + j, i * m + j - 1);
					if (j < m - 1 && map[i][j + 1] != 'x') addEdge(i * m + j, i * m + j + 1);
				}
			}
		}
		spfa(0);
		bool flag = false;
		for (int i = 1; i < cnt; i++) {
			if (dist[0][vertex[i]] == INF) {
				printf("-1\n");
				flag = true;
				break;
			}
		}
		if (flag) continue;
		for (int i = 1; i < cnt; i++) spfa(i);
		ans = INF;
		memset(vis, 0, sizeof(vis));
		dfs(1, 0, 0);
		cout << ans << endl;
	}
	return 0;
}
