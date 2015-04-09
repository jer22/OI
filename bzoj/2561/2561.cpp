#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 100000;

/**
	储存弧的结构
	代表从from到to，容量为cap， 流量为flow
*/
struct Edge{
	int from, to, cap, flow;
};

int V, E, S, T;
vector<Edge> edges; // 边 edges[e]和edges[e ^ 1]互为反向弧
vector<int> G[MAXV]; // 邻接表 G[i][j]表示节点i的第j条边在edges中的序号
int layer[MAXV];	// 节点i的层
int cur[MAXV];		// 当前弧下标

/**
	插入弧
	将插入两条弧，一条是它本身，一条是它的反向弧
	edges[i]与edges[i ^ 1]互为反向弧
*/
void addEdge(int from, int to, int cap) {
	edges.push_back((Edge){from, to, cap, 0});
	edges.push_back((Edge){to, from, 0, 0});
	E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
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
			if (layer[e.to] == -1 && e.cap > e.flow) { // 只考虑残量网络中的弧
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
	int flow = 0;
	int f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap - e.flow))) != 0) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic(int s, int t) {
	S = s, T = t;
	int flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(s, INF);
	}
	return flow;
}

vector<Edge> tree;
int main( void ) {
	freopen("2561.in", "r", stdin);
	scanf("%d %d", &V, &E);
	int e = E;
	int x, y, l;
	for (int i = 0; i < e; i++) {
		scanf("%d %d %d", &x, &y, &l);
		tree.push_back((Edge){x, y, l, 0});
	}
	scanf("%d %d %d", &x, &y, &l);
	for (int i = 0; i < tree.size(); i++) {
		Edge e = tree[i];
		if (e.cap < l) {
			addEdge(e.from, e.to, 1);
			addEdge(e.to, e.from, 1);
		}
	}
	int ans1 = dinic(x, y);
	edges.clear();
	for (int i = 1; i <= V; i++)
		G[i].clear();
	for (int i = 0; i < tree.size(); i++) {
		Edge e = tree[i];
		if (e.cap > l) {
			addEdge(e.from, e.to, 1);
			addEdge(e.to, e.from, 1);
		}
	}
	int ans2 = dinic(x, y);
	printf("%d\n", ans1 + ans2);

	return 0;
}
