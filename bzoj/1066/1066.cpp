#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define p(i, j) (i - 1) * m + j
#define MAXN 1005

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
vector<int> G[MAXN]; // 邻接表 G[i][j]表示节点i的第j条边在edges中的序号
int layer[MAXN];	// 节点i的层
int cur[MAXN];		// 当前弧下标

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

int d;
char e[25][25], v[25][25];
int main() {
	freopen("1066.in", "r", stdin);
	cin >> n >> m >> d;
	for (int i = 1; i <= n; i++)
		cin >> e[i] + 1;
	for (int i = 1; i <= n; i++)
		cin >> v[i] + 1;
	S = 0, T = 1003;
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int h = e[i][j] - '0';
			if (h)
				addEdge(p(i, j), p(i, j) + n * m, h);
			if (i <= d || j <= d || i + d > n || j + d > m)
				addEdge(p(i, j) + n * m, T, INF);
			if (v[i][j] == 'L')
				addEdge(S, p(i, j), 1), tot++;
			for (int k = 1; k <= n; k++) {
				for (int l = 1; l <= m; l++) {
					if (i == k && j == l) continue;
					if (sqrt(abs(i - k) * abs(i - k) + abs(j - l) * abs(j - l)) <= d) {
						addEdge(p(i, j) + n * m, p(k, l), INF);
					}
				}
			}
		}
	}
	cout << tot - dinic() << endl;

	return 0;
}
