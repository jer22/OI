#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
};

struct Edge{
	int from, to, v;
	Edge() {}
	Edge(int a, int b, int c) : from(a), to(b), v(c) {}
	bool operator < (const Edge &e) const {
		return v < e.v;
	}
};

int n, m, p, q;
char arr[2005][2005];
int vis[2005][2005];
int dist[2005][2005];
Point buildings[MAXN];
queue<Point> qu;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool check(int i, int j) {
	if (i < 1 || i > n || j < 1 || j > m) return false;
	return (arr[i][j] == '.');
}

void bfs() {
	while (!qu.empty()) {
		Point cur = qu.front();
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (!check(nx, ny)) continue;
			if (vis[nx][ny]) continue;
			vis[nx][ny] = vis[cur.x][cur.y];
			dist[nx][ny] = dist[cur.x][cur.y] + 1;
			qu.push(Point(nx, ny));
		}
	}
}

vector<Edge> edges[MAXN];
vector<Edge> es;

void addEdge(int i, int j, int v) {
	es.push_back(Edge(i, j, v));
	// edges[i].push_back(Edge(j, v));
	// edges[j].push_back(Edge(i, v));
}
int father[MAXN];
int findfa(int p) {
	if (p == father[p]) return p;
	return father[p] = findfa(father[p]);
}

int fa[MAXN][24], deep[MAXN], ma[MAXN][24];

void dfs(int x) {

	for (int i = 1; (1 << i) <= deep[x]; i++) {
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
		ma[x][i] = max(ma[x][i - 1], ma[fa[x][i - 1]][i - 1]);
	}
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == fa[x][0]) continue;
		fa[e.to][0] = x;
		ma[e.to][0] = e.v;
		deep[e.to] = deep[x] + 1;
		dfs(e.to);
	}
}

int query(int x, int y) {
	if (findfa(x) != findfa(y)) return -1;
	if (deep[x] < deep[y]) swap(x, y);

	int tmp = deep[x] - deep[y];
	int ans = 0;
	for (int i = 0; (1 << i) <= tmp; i++) {
		if (tmp & (1 << i)) {
			ans = max(ans, ma[x][i]);
			x = fa[x][i];
		}
	}

	for (int i = 17; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			ans = max(ans, max(ma[x][i], ma[y][i]));
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	if (x != y) ans = max(ans, max(ma[x][0], ma[y][0]));
	return ans;
}

int main() {
	freopen("4242.in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &p, &q);
	char ch = getchar();
	for (int i = 1; i <= n; i++){  
		while (ch != '.' && ch != '#') ch = getchar();  
		for (int j = 1; j <= m; j++, ch = getchar())  
			arr[i][j] = ch;  
	}
	for (int i = 1; i <= p; i++) {
		father[i] = i;
		scanf("%d %d", &buildings[i].x, &buildings[i].y);
		vis[buildings[i].x][buildings[i].y] = i;
		qu.push(buildings[i]);
	}
	bfs();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!check(i, j)) continue;
			if (check(i + 1, j) && (vis[i][j] != vis[i + 1][j]))
				addEdge(vis[i][j], vis[i + 1][j], dist[i][j] + dist[i + 1][j]);
			if (check(i, j + 1) && (vis[i][j] != vis[i][j + 1]))
				addEdge(vis[i][j], vis[i][j + 1], dist[i][j] + dist[i][j + 1]);
		}
	}

	sort(es.begin(), es.end());
	for (int i = 0; i < es.size(); i++) {
		int a = es[i].from, b = es[i].to, c = es[i].v;
		int x = findfa(a), y = findfa(b);
		if (x == y) continue;
		edges[a].push_back(Edge(a, b, c));
		edges[b].push_back(Edge(b, a, c));
		father[x] = y;
		// cout << a << ' ' << b << endl;
	}
	for (int i = 1; i <= p; i++) {
		// cout << findfa(i) << endl;
		if (findfa(i) == i) {
			deep[i] = 1;
			dfs(i);
		}
	}
	int a, b;

	while (q--) {
		scanf("%d %d", &a, &b);
		printf("%d\n", query(a, b));
	}

	return 0;
}
