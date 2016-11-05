#include <bits/stdc++.h>

#define S 0
#define T n + 3

using namespace std;

const int MAXN = 3005;
const int INF = 0x3f3f3f3f;

struct Edge{
	int from, to, cap, flow, cost;
	Edge(int u, int v, int c, int f, int x)
		: from(u), to(v), cap(c), flow(f), cost(x) {}
};

int n, p, s;
vector<int> G[MAXN];
vector<Edge> edges;
bool done[MAXN];
int dist[MAXN];
int pre[MAXN];
int f[MAXN];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

bool spfa(int& flow, int& cost) {
	memset(dist, 0x3f, sizeof(dist));
	memset(done, 0, sizeof(done));
	dist[S] = 0;
	done[S] = 1;
	pre[S] = 0;
	f[S] = INF;
	queue<int> buff;
	buff.push(S);
	while(!buff.empty()) {
		int current = buff.front();
		buff.pop();
		done[current] = 0;
		for (int i = 0; i < G[current].size(); i++) {
			Edge& e = edges[G[current][i]];
			if (e.cap > e.flow && dist[e.to] > dist[current] + e.cost) {
				dist[e.to] = dist[current] + e.cost;
				pre[e.to] = G[current][i];
				f[e.to] = min(f[current], e.cap - e.flow);
				if (!done[e.to]) {
					done[e.to] = 1;
					buff.push(e.to);
				}
			}
		}
	}
	if (dist[T] == INF)
		return false;
	flow += f[T];
	cost += dist[T] * f[T];
	for (int u = T; u != S; u = edges[pre[u]].from) {
		edges[pre[u]].flow += f[T];
		edges[pre[u] ^ 1].flow -= f[T];
	}
	return true;
}

int minCostMaxFlow() {
	int flow = 0, cost = 0;
	while(spfa(flow, cost));
	return cost;
}

int a[MAXN], b[MAXN];
int main() {
	// freopen("i.in", "r", stdin);
	cin >> n >> p >> s;
	for (int i = 1; i <= n; i++)
		addEdge(S, i, 1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		addEdge(i, n + 1, 1, -a[i]);
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		addEdge(i, n + 2, 1, -b[i]);
	}
	addEdge(n + 1, T, p, 0);
	addEdge(n + 2, T, s, 0);
	cout << -minCostMaxFlow() << endl;
	for (int i = n << 1; i < n << 2; i += 2) {
		if (edges[i].flow == 1) cout << (i >> 1) - n + 1 << ' ';
	}
	cout << endl;
	for (int i = n << 2; i < n * 6; i += 2) {
		if (edges[i].flow == 1) cout << (i >> 1) - (n << 1) + 1 << ' ';
	}
	cout << endl;
	return 0;
}
