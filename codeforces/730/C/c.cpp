#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
const int INF = 0x3f3f3f3f;

struct Node{
	int dis;
	long long tot, cos;
	Node() {}
	Node(int a, long long b, long long c) : dis(a), tot(b), cos(c) {}
	bool operator < (const Node &n) const {
		return cos < n.cos;
	}
};

int n, m, w;
vector<int> edges[MAXN];
int dist[MAXN];
bool vis[MAXN];
long long sto[MAXN][3];
int mx[1005];
vector<Node> rea[1005];
int querys[1005][3];

bool good(int x, int len, long long num, long long money) {
	long long now = 0;
	for (int i = 0; i < rea[x].size(); i++) {
		if (rea[x][i].dis > len) continue;
		now += min(num, rea[x][i].tot) * rea[x][i].cos;
		num -= min(rea[x][i].tot, num);
		if (!num) break;
		if (now > money) return false;
	}
	if (now > money) return false;
	if (num) return false;
	return true;
}

void spfa(int s) {
	queue<int> q;
	q.push(querys[s][0]);
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[querys[s][0]] = 0;
	vis[querys[s][0]] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (int i = 0; i < edges[cur].size(); i++) {
			int nex = edges[cur][i];
			if (dist[cur] + 1 < dist[nex]) {
				dist[nex] = dist[cur] + 1;
				if (!vis[nex]) {
					vis[nex] = 1;
					q.push(nex);
				}
			}
		}
	}
	for (int i = 1; i <= w; i++) {
		if (dist[sto[i][0]] == INF) continue;
		rea[s].push_back(Node(dist[sto[i][0]], sto[i][1], sto[i][2]));
		mx[s] = max(mx[s], dist[sto[i][0]]);
	}
	sort(rea[s].begin(), rea[s].end());
}

int main() {
	// freopen("c.in", "r", stdin);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	memset(mx, -1, sizeof(mx));
	cin >> n >> m;
	int a, b;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	cin >> w;
	for (int i = 1; i <= w; i++)
		cin >> sto[i][0] >> sto[i][1] >> sto[i][2];
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++) {
		cin >> querys[i][0] >> querys[i][1] >> querys[i][2];
	}
	for (int i = 1; i <= q; i++)
		spfa(i);
	long long x, num, money;
	for (int i = 1; i <= q; i++) {
		x = querys[i][0], num = querys[i][1], money = querys[i][2];
		int l = 0, r = mx[i];
		if (r < 0) {
			if (!num) cout << 0 << endl;
			else cout << -1 << endl;
			continue;
		}
		while (l < r) {
			int m = l + r >> 1;
			bool f = good(i, m, num, money);
			if (f) r = m;
			else l = m + 1;
		}
		if (!good(i, l, num, money)) cout << -1 << endl;
		else cout << l << endl;
	}
	return 0;
}
