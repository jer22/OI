#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

#define INF 0x3f3f3f3f
#define MAXV 12000
#define T (n * 101 + m + 1)

using namespace std;

struct Edge{
	int from, to, cap, flow;
};

int n, m;
vector<Edge> edges; // 边 edges[e]和edges[e + 1]互为反向弧
vector<int> G[MAXV]; // 邻接表 G[i][j]表示节点i的第j条边在edges中的序号
bool vis[MAXV];		// build方法中使用，表示的i条边有没有被标号过
int layer[MAXV];	// 节点i的层
int cur[MAXV];

void addEdge(int from, int to, int cap) {
	Edge temp;
	temp.from = from;
	temp.to = to;
	temp.cap = cap;
	temp.flow = 0;
	edges.push_back(temp);
	temp.from = to;
	temp.to = from;
	temp.cap = 0;
	temp.flow = 0;
	edges.push_back(temp);
	int E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
}

bool build() {
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(0);
	layer[0] = 0;
	vis[0] = 1;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (!vis[e.to] && e.cap > e.flow) {
				vis[e.to] = 1;
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return vis[T];
}

int find(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0;
	int f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap - e.flow))) != 0) {
			e.flow += f;
			edges[G[x][i] + 1].flow -= f;
			flow += f;
			a -= f;
			if (!a)
				break;
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

int main() {
	freopen("p1555.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &t);
			if (t == 1) addEdge(i * 101 + j, T, INF);
			if (t == 2) addEdge(0, i * 101 + j, INF);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			addEdge(i * 101 + j, i * 101 + j + 1, 1);
			addEdge(i * 101 + j + 1, i * 101 + j, 1);
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			addEdge(i * 101 + j, (i + 1) * 101 + j, 1);
			addEdge((i + 1) * 101 + j, i * 101 + j, 1);
		}
	}
	int ans = dinic();

	printf("%d\n", ans);
	return 0;
}
