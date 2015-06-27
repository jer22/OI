#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;

int n, m;
vector<int> edges[MAXN];
int s1, t1, s2, t2, k1, k2;
int dist[MAXN][MAXN];
bool vis[MAXN];

void spfa(int s) {
	memset(dist[s], 0x3f, sizeof(dist[s]));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[s][s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			int nex = edges[cur][i];
			if (dist[s][cur] + 1 < dist[s][nex]) {
				dist[s][nex] = dist[s][cur] + 1;
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
	// freopen("d.in", "r", stdin);
	cin >> n >> m;
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	cin >> s1 >> t1 >> k1;
	cin >> s2 >> t2 >> k2;
	if (m == 0) {
		cout << 0 << endl;
		return 0;
	}
	for (int i = 1; i <= n; i++)
		spfa(i);
	if (dist[s1][t1] > k1 || dist[s2][k2] > k2) {
		cout << "-1" << endl;
		return 0;
	}
	int ans = 0x3f3f3f3f;
	int dist1, dist2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist1 = dist[s1][i] + dist[i][j] + dist[j][t1];
			dist2 = dist[s2][i] + dist[i][j] + dist[j][t2];
			if (dist1 <= k1 && dist2 <= k2) {
				ans = min(ans, dist[s1][i] + dist[j][t1] + dist[s2][i] + dist[j][t2] + dist[i][j]);
			}
			dist1 = dist[s1][i] + dist[i][j] + dist[j][t1];
			dist2 = dist[s2][j] + dist[j][i] + dist[i][t2];
			if (dist1 <= k1 && dist2 <= k2) {
				ans = min(ans, dist[s1][i] + dist[j][t1] + dist[s2][j] + dist[i][t2] + dist[i][j]);
			}
			dist1 = dist[s1][j] + dist[i][j] + dist[i][t1];
			dist2 = dist[s2][i] + dist[j][i] + dist[j][t2];
			if (dist1 <= k1 && dist2 <= k2) {
				ans = min(ans, dist[s1][j] + dist[i][t1] + dist[s2][i] + dist[j][t2] + dist[i][j]);
			}
			dist1 = dist[s1][j] + dist[i][j] + dist[i][t1];
			dist2 = dist[s2][j] + dist[j][i] + dist[i][t2];
			if (dist1 <= k1 && dist2 <= k2) {
				ans = min(ans, dist[s1][j] + dist[i][t1] + dist[s2][j] + dist[i][t2] + dist[i][j]);
			}
		}
	}
	ans = min(ans, dist[s1][t1] + dist[s2][t2]);
	cout << m - ans << endl;

	return 0;
}
