#include <bits/stdc++.h>

#define p(i, j) (((i) - 1) * m + (j))
#define T 603

using namespace std;

const int MAXN = 605;
const int INF = 0x3f3f3f3f;

struct Edge{
	int to;
	int cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];
int arr[MAXN], deg[MAXN];
bool vis[MAXN];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(0);
	layer[0] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap))) != 0) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(0, INF);
	}
	return flow;
}

vector<int> ee[MAXN];
void insert(int from, int to) {
	ee[from].push_back(to);
}

void topo() {
	queue<int> q;
	for (int i = 1; i <= p(n, m); i++)
		if (!deg[i]) q.push(i), vis[i] = 1;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < ee[x].size(); i++)
			if (!--deg[ee[x][i]]) q.push(ee[x][i]), vis[ee[x][i]] = 1;
	}
}

int tot = 0;
void rebuild() {
	for (int i = 1; i <= p(n, m); i++) {
		if (!vis[i]) continue;
		for (int j = 0; j < ee[i].size(); j++) {
			if (!vis[ee[i][j]]) continue;
			addEdge(i, ee[i][j], INF);
		}
		if (arr[i] > 0) {
			tot += arr[i];
			addEdge(i, T, arr[i]);
		} else addEdge(0, i, -arr[i]);
	}
}

int main() {
	freopen("1565.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int x, k, a, b;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d %d", &x, &k);
			arr[p(i, j)] = x;
			while (k--) {
				scanf("%d %d", &a, &b);
				a++, b++;
				insert(p(i, j), p(a, b));
				deg[p(a, b)]++;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			insert(p(i, j + 1), p(i, j));
			deg[p(i, j)]++;
		}
	}
	topo();
	rebuild();
	printf("%d\n", tot - dinic());
	
	return 0;
}
