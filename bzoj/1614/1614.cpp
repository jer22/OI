#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1005;
const int INF = 0x7f7f7f7f;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

struct Node{
	int v, k;
	Node() {}
	Node(int a, int b) : v(a), k(b) {}
};

int n, m, k;
vector<Edge> edges[MAXN];
int dist[MAXN][MAXN];
bool vis[MAXN][MAXN];
queue<Node> q;

int spfa() {
	memset(dist, 0x7f, sizeof(dist));
	dist[1][k] = 0;
	vis[1][k] = 1;
	q.push(Node(1, k));
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		vis[cur.v][cur.k] = 0;
		for (int i = 0; i < edges[cur.v].size(); i++) {
			Edge e = edges[cur.v][i];
			// remove
			if (cur.k && e.v > dist[cur.v][cur.k]) {
				if (dist[cur.v][cur.k] < dist[e.to][cur.k - 1]) {
					dist[e.to][cur.k - 1] = dist[cur.v][cur.k];
					if (!vis[e.to][cur.k - 1]) {
						vis[e.to][cur.k - 1] = 1;
						q.push(Node(e.to, cur.k - 1));
					}
				}
			}
			// not remove
			if (max(dist[cur.v][cur.k], e.v) < dist[e.to][cur.k]) {
				dist[e.to][cur.k] = max(dist[cur.v][cur.k], e.v);
				if (!vis[e.to][cur.k]) {
					vis[e.to][cur.k] = 1;
					q.push(Node(e.to, cur.k));
				}
			}
		}
	}
	int ans = INF;
	for (int i = 0; i <= k; i++)
		ans = min(ans, dist[n][i]);
	return ans;
}

int main() {
	freopen("1614.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	int ans = spfa();
	if (ans == INF) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}
