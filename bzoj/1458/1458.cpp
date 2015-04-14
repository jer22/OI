#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXV 205

using namespace std;

int n, m, k;
int l[105], c[105], totl[105], totc[105];
bool fuck[105][105];

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

int main() {
	freopen("1458.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= m; i++)
		cin >> l[i], totl[i] = n;
	for (int i = 1; i <= n; i++)
		cin >> c[i], totc[i] = m;
	int a, b;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		if (--totl[a] < l[a] || --totc[b] < c[b]) {
			cout << "JIONG" << endl;
			return 0;
		}
		fuck[a][b] = 1;
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (!fuck[i][j]) addEdge(i, j + n, 1);
	for (int i = 1; i <= m; i++)
		addEdge(0, i, totl[i] - l[i]);
	for (int i = 1; i <= n; i++)
		addEdge(i + n, n + n + 1, totc[i] - c[i]);

	cout << n * m - k - dinic(0, n + n + 1) << endl;

	return 0;
}
