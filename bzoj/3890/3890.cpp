#include <bits/stdc++.h>

#define INF 0x7f7f7f7f

using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0'&& ch <= '9') { x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}

struct Edge{
	int to, v[2];
	Edge() {}
	Edge(int a, int b, int c) {
		to = a, v[0] = b, v[1] = c;
	}
};

struct Node{
	int v, tot, dist;
	Node() {}
	Node(int a, int b, int c) : v(a), dist(b), tot(c) {}
	bool operator < (const Node &n) const {
		if (tot != n.tot) return tot > n.tot;
		return dist < n.dist;
	}
};

int n, m;
vector<Edge> edges[105];
vector<Edge> redges[105];
int dis[2][105], q[1000];
bool vis[105];

void spfa_init(int id) {
	memset(dis[id], 0x7f, sizeof(dis[id]));
	memset(vis, 0, sizeof(vis));
	int h = 1, t = 1;
	dis[id][n] = 0, vis[n] = 1, q[t++] = n;
	while (h < t) {
		int cur = q[h++];
		for (int i = 0; i < redges[cur].size(); i++) {
			Edge e = redges[cur][i];
			if (dis[id][cur] + e.v[id] < dis[id][e.to]) {
				dis[id][e.to] = dis[id][cur] + e.v[id];
				if (!vis[e.to]) vis[e.to] = 1, q[t++] = e.to;
			}
		}
		vis[cur] = 0;
	}
}

int ans[2][25];
int spfa_Astar(int id) {
	if (dis[id][1] == 0x7f7f7f7f) return -1;
	priority_queue<Node> q;
	q.push(Node(1, 0, dis[id][1]));
	int cnt = 0;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		if (cur.v == n) {
			ans[id][cnt++] = cur.dist;
			if (cnt == 20) return cnt;
		}
		for (int i = 0; i < edges[cur.v].size(); i++) {
			Edge e = edges[cur.v][i];
			q.push(Node(e.to, cur.dist + e.v[id], cur.dist + e.v[id] + dis[id][e.to]));
		}
	}
	return cnt;
}

int main() {
	n = read();
	m = read();
	int a, b, c, d;
	for (int i = 0; i < m; i++) {
		a = read();
		b = read();
		c = read();
		d = read();
		edges[a].push_back(Edge(b, c, d));
		redges[b].push_back(Edge(a, c, d));
	}
	spfa_init(0);
	spfa_init(1);
	int cnt1 = spfa_Astar(0);
	int cnt2 = spfa_Astar(1);
	if (cnt1 == -1 || cnt2 == -1) {
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	int res = 0x7f7f7f7f;
	bool flag = false;
	for (int i = 0; i < cnt1; i++)
		for (int j = 0; j < cnt2; j++)
			if (ans[0][i] == ans[1][j])
				res = min(ans[0][i], res);
	if (res == 0x7f7f7f7f) cout << "IMPOSSIBLE" << endl;
	else cout << res << endl;
	return 0;
}
