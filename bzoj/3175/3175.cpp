#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

#define p(i, j) (i * V + j)

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 40005;

/**
	储存弧的结构
	代表从from到to，容量为cap， 流量为flow
*/
struct Edge{
	int from, to, cap, flow;
};

char fuck[205][205];
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

bool check(int x, int y) {
	if (fuck[x][y] == '1') return false;
	if (x < 0 || x >= V || y < 0 || y >= V) return false;
	return true;
}

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

int dir[8][2] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
int main() {
	freopen("3175.in", "r", stdin);
	scanf("%d", &V);
	int tot = 0;
	for (int i = 0; i < V; i++)
		scanf("%s", fuck[i]);
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (fuck[i][j] == '0') tot++;
			if ((i + j) & 1) addEdge(p(i, j), V * V + 1, 1);
			else addEdge(0, p(i, j), 1);
		}
	}
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if ((i + j) & 1) continue;
			if (fuck[i][j] == '1') continue;
			int p = p(i, j);
			for (int k = 0; k < 8; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (check(nx, ny)) {
					int q = p(nx, ny);
					addEdge(p, q, INF);
				}
			}
		}
	}

	printf("%d\n", tot - dinic(0, V * V + 1));
	return 0;
}
