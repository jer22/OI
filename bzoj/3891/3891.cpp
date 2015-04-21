#include <bits/stdc++.h>

using namespace std;

int val[3], n, m;
vector<int> edges[40005];
int dist[3][40005];
bool vis[40005];
void spfa(int s, int id) {
	memset(dist[id], 0x7f, sizeof(dist[id]));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[id][s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			int nex = edges[cur][i];
			if (dist[id][cur] + val[id] < dist[id][nex]) {
				dist[id][nex] = dist[id][cur] + val[id];
				if (!vis[nex]) {
					vis[nex] = 1;
					q.push(nex);
				}
			}
		}
		vis[cur] = 0;
	}
}

int main() {
	freopen("3891.in", "r", stdin);
	cin >> val[0] >> val[1] >> val[2] >> n >> m;
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	spfa(1, 0);
	spfa(2, 1);
	spfa(n, 2);
	int ans = 0x7f7f7f7f;
	for (int i = 1; i <= n; i++)
		ans = min(ans, dist[0][i] + dist[1][i] + dist[2][i]);
	cout << ans << endl;
	return 0;
}
