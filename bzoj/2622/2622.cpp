#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, k;
vector<pair<int, int> > edges[MAXN];
int dist[MAXN][2];
bool vis[MAXN];
int pre[MAXN];

void spfa() {
	queue<int> q;
	for (int i = 0, x; i < k; i++) {
		scanf("%d", &x);
		vis[x] = 1;
		dist[x][0] = dist[x][1] = 0;
		q.push(x);
	}
	
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (int i = 0; i < edges[cur].size(); i++) {
			int to = edges[cur][i].first, v = edges[cur][i].second;
			if (dist[cur][1] + v <= dist[to][0]) {
				if (pre[to] != cur) {
					dist[to][1] = dist[to][0];
					if (!vis[to]) {
						q.push(to);
						vis[to] = 1;
					}
				}
				pre[to] = cur;
				dist[to][0] = dist[cur][1] + v;
			} else if (dist[cur][1] + v < dist[to][1]) {
				dist[to][1] = dist[cur][1] + v;
				if (!vis[to]) {
					q.push(to);
					vis[to] = 1;
				}
			}
		}
	}
}

int main() {
	freopen("2622.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0, a, b, c; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back({b, c});
		edges[b].push_back({a, c});
	}
	memset(dist, 0x3f, sizeof(dist));
	memset(pre, -1, sizeof(pre));
	spfa();
	
	printf("%d\n", dist[0][1]);

	return 0;
}
