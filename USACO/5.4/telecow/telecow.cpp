/*
ID:shijiey1
LANG:C++
PROG:telecow
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define T (t)
#define S (s + V)

using namespace std;

struct Edge{
	int from, to, cap, flow;
};

int V, E, s, t;
vector<Edge> edges;
vector<int> G[210];
int cut[210];
int arr[210][210];
void addEdge(int from, int to, int value) {
	Edge e;
	e.from = from;
	e.to = to;
	e.cap = value;
	e.flow = 0;
	edges.push_back(e);
	e.from = to;
	e.to = from;
	e.cap = 0;
	edges.push_back(e);
	int a = edges.size();
	G[from].push_back(a - 2);
	G[to].push_back(a - 1);
}

void makeGraph() {
	edges.clear();
	for (int i = 0; i <= T; i++) G[i].clear();
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			if (arr[i][j]) addEdge(i + V, j, INF);
		}
	}
	for (int i = 1; i <= V; i++) {
		if (!cut[i]) addEdge(i, i + V, 1);
		else addEdge(i, i + V, 0);
	}
	// addEdge(0, s + V, INF);
	// addEdge(t + V, T, INF);
}

int layer[210];
int done[210];
bool build() {
	memset(layer, -1, sizeof(layer));
	memset(done, 0, sizeof(done));
	queue<int> q;
	done[S] = 1;
	layer[S] = 0;
	q.push(S);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge e = edges[G[x][i]];
			if (cut[e.to]) continue;
			if (!done[e.to] && e.cap > e.flow) {
				layer[e.to] = layer[x] + 1;
				done[e.to] = 1;
				q.push(e.to);
			}
		}
	}
	return done[T];
}

int cur[210];
int find(int x, int a) {
	if (x == T || !a) return a;
	int flow = 0;
	int f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (cut[e.to]) continue;
		if (layer[e.to] == layer[x] + 1
			&& (f = find(e.to, min(e.cap - e.flow, a))) != 0) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(S, INF);
	}
	return ans;
}

int res[210];
int cnt = 0;
int main() {
	freopen("telecow.in", "r", stdin);
	freopen("telecow.out", "w", stdout);
	cin >> V >> E >> s >> t;
	int a, b;
	for (int i = 0; i < E; i++) {
		cin >> a >> b;
		arr[a][b] = arr[b][a] = 1;
	}
	makeGraph();
	int ans = dinic();
	cout << ans << endl;
	for (int i = 1; i <= V && ans; i++) {
		if (i == s || i == t) continue;
		cut[i] = 1;
		makeGraph();
		if (dinic() < ans) {
			ans--;
			res[cnt++] = i;
		} else {
			cut[i] = 0;
		}
	}
	for (int i = 0; i < cnt; i++) {
		if (i) cout << ' ';
		cout << res[i];
	}
	cout << endl;
	return 0;
}
