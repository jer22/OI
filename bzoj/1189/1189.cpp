/****************************************


这个代码是错的。
我真是日了狗了。
草草草草草草草草草草草草草草草草草草草草草草草草草草草草草草草
TMD调了一万年，NMB我草老子真是服了


****************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 3005
#define p(i, j) (((i) - 1) * m + (j))

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

char e[25][25];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int ndoor = 0;
int doors[105];
int dist[405][405];
bool vis[405];

bool check(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return false;
	if (e[x][y] == 'X') return false;
	return true;
}

void spfa(int s) {
	++ndoor;
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(s);
	dist[ndoor][s] = 0;
	vis[s] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		int x = (cur - 1) / m + 1, y = (cur - 1) % m + 1;
		for (int i = 0; i < 4; i++) {
			int nx = x + dir[i][0], ny = y + dir[i][1];
			if (!check(nx, ny)) continue;
			int nex = p(nx, ny);
			if (dist[ndoor][cur] + 1 < dist[ndoor][nex]) {
				dist[ndoor][nex] = dist[ndoor][cur] + 1;
				if (!vis[nex]) {
					vis[nex] = 1;
					q.push(nex);
				}
			}
		}
		vis[cur] = 0;
	}
}

int tot = 0;
void build_graph(int x) {
	edges.clear();
	for (int i = 0; i <= T; i++)
		G[i].clear();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (e[i][j] == '.') addEdge(S, p(i, j), 1);
	for (int i = 1; i <= ndoor; i++)
		addEdge(n * m + i + 1, T, x);
	for (int i = 1; i <= ndoor; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= m; k++) {
				if (e[j][k] != '.') continue;
				if (dist[i][p(j, k)] <= x) {
					addEdge(p(j, k), n * m + i + 1, x);
				}
			}
		}
	}
}

int solve() {
	int ans = -1;
	int l = 0, r = 400;
	while (l <= r) {
		int mid = l + r >> 1;
		build_graph(mid);
		if (dinic() == tot) {
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return ans;
}

int main() {
	freopen("1189.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", e[i] + 1);
	S = 0, T = 3003;
	memset(dist, 0x3f, sizeof(dist));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (e[i][j] == 'D') spfa(p(i, j));
			else if (e[i][j] == '.') tot++;

	int ans = solve();
	if (ans == -1) printf("impossible\n");
	else printf("%d\n", ans);;

	return 0;
}
