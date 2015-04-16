#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

/**
	储存弧的结构
	代表从from到to，容量为cap， 流量为flow
*/
struct Edge{
	int to, cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

int n, m, S, T;
vector<Edge> edges; // 边 edges[e]和edges[e ^ 1]互为反向弧
vector<int> G[20005]; // 邻接表 G[i][j]表示节点i的第j条边在edges中的序号
int layer[20005];	// 节点i的层
int cur[20005];		// 当前弧下标

/**
	插入弧
	将插入两条弧，一条是它本身，一条是它的反向弧
	edges[i]与edges[i ^ 1]互为反向弧
*/
void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

/**
	建立层次图
	@return：是否存在s-t路径
*/
bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(S);
	layer[S] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > 0) { // 只考虑残量网络中的弧
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

/**
	寻找增广路
	@param x：当前节点
	@param a：目前为止所有弧的最小残量
	@return：流量
*/
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
		flow += find(S, INF);
	}
	return flow;
}

int a[10005], b[10005];

void build_graph(int x) {
	edges.clear();
	for (int i = 0; i < 20003; i++)
		G[i].clear();
	for (int i = 1; i <= m; i++) {
		addEdge(S, i + n, 1);
		addEdge(i + n, a[i], 1);
		addEdge(i + n, b[i], 1);
	}
	for (int i = 1; i <= n; i++)
		addEdge(i, T, x);
}

int solve() {
	int l = 0, r = 5000;
	S = 0, T = n + m + 1;
	while (l < r) {
		int mid = l + r >> 1;
		build_graph(mid);
		if (dinic() == m) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main() {
	freopen("1532.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d %d", &a[i], &b[i]);
	printf("%d\n", solve());

	return 0;
}
