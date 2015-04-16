#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define MAXN 55

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

int dinic(int s, int t) {
	S = s, T = t;
	int flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(S, INF);
	}
	return flow;
}

int sa, ta, sb, tb, na, nb;
char e[55][55];

void build_graph() {
	edges.clear();
	for (int i = 0; i <= n; i++)
		G[i].clear();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (e[i][j] == 'O') addEdge(i, j, 2);
			if (e[i][j] == 'N') addEdge(i, j, INF);
		}
	}
}

int main() {
	freopen("3504.in", "r", stdin);
	while (cin >> n >> sa >> ta >> na >> sb >> tb >> nb) {
		sa++, sb++, ta++, tb++;
		for (int i = 1; i <= n; i++)
			cin >> e[i] + 1;
		build_graph();
		addEdge(ta, n + 1, na << 1);
		addEdge(tb, n + 1, nb << 1);
		addEdge(0, sa, na << 1);
		addEdge(0, sb, nb << 1);
		bool flag = true;
		int tot = (na << 1) + (nb << 1);
		if (dinic(0, n + 1) >= tot) {
			build_graph();
			addEdge(ta, n + 1, na << 1);
			addEdge(sb, n + 1, nb << 1);
			addEdge(0, sa, na << 1);
			addEdge(0, tb, nb << 1);
			if (dinic(0, n + 1) < tot) flag = false;
		} else flag = false;
		if (flag) cout << "Yes" << endl;
		else cout << "No" << endl;
	}




	return 0;
}
