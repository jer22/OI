#include <bits/stdc++.h>

#define INF INT_MAX
#define MAXN 10005
#define S 0
#define T 10003

using namespace std;

int n, m;
char str[105][105];
int arr[105][105];

struct Edge{
	int to;
	int cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

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
		flow += find(S, INF);
	}
	return flow;
}


int cnt = 0;
int ans[MAXN];
int col[MAXN];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool vis[MAXN];

void dfs(int v, int d) {
	// cout << col[v] << ' ' << d << endl;
	vis[v] = 1;
	if (col[v] == d && v && v != T)
		ans[cnt++] = v;
	for (int i = 0; i < G[v].size(); i++) {
		Edge e = edges[G[v][i]];
		if (e.cap == d && !vis[e.to])
			dfs(e.to, d);
	}
}

int x[MAXN], y[MAXN];

int main() {
	freopen("1443.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", str[i] + 1);
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str[i][j] == '.') {
				arr[i][j] = ++tot;
				x[tot] = i;
				y[tot] = j;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str[i][j] == '.') {
				if ((i + j) & 1) {
					addEdge(S, arr[i][j], 1);
					col[arr[i][j]] = 1;
					for (int k = 0; k < 4; k++) {
						int nx = i + dir[k][0];
						int ny = j + dir[k][1];
						if (arr[nx][ny]) addEdge(arr[i][j], arr[nx][ny], 1);
					}
				} else addEdge(arr[i][j], T, 1);
			}
		}
	}
	dinic();

	dfs(S, 1);
	memset(vis, 0, sizeof(vis));
	dfs(T, 0);

	if (cnt) printf("WIN\n");
	else printf("LOSE\n");
	sort(ans, ans + cnt);
	for (int i = 0; i < cnt; i++)
		printf("%d %d\n", x[ans[i]], y[ans[i]]);

	return 0;
}
