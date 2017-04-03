#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#define INF INT_MAX
#define S 0
#define T (tot + 1)

using namespace std;
const int MAXN = 20005;

int n, m;
vector<pair<int, int> > ge[MAXN];
int fa[MAXN][18];
int idp[MAXN][18], id[MAXN], idm[MAXN], tot = 0;
struct Edge{
	int to;
	long long cap;
	Edge() {}
	Edge(int a, long long b) : to(a), cap(b) {}
};

vector<Edge> edges;
vector<int> G[MAXN << 4];
int layer[MAXN << 4];
int cur[MAXN << 4];

void addEdge(int from, int to, long long cap) {
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

long long find(int x, long long a) {
	if (x == T || a == 0) return a;
	long long flow = 0, f;
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

long long dinic() {
	long long flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(S, INF);
	}
	return flow;
}
int dep[MAXN], mm[MAXN];
void dfs(int x, int pre, int y) {
	dep[x] = dep[pre] + 1;
	if (pre) {
		idp[x][0] = ++tot;
		idm[x] = ++tot;
		mm[x] = y;
		addEdge(idp[x][0], idm[x], INF);
		fa[x][0] = pre;
	}
	for (int i = 1; i <= 15; i++) {
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
		if (fa[x][i]) {
			idp[x][i] = ++tot;
			addEdge(idp[x][i], idp[x][i - 1], INF);
			addEdge(idp[x][i], idp[fa[x][i - 1]][i - 1], INF);
		} else break;
	}

	for (auto nex : ge[x])
		if (nex.first != pre) dfs(nex.first, x, nex.second);
}

void solve(int a, int b, int x) {
	if (dep[a] < dep[b]) swap(a, b);
	int t = dep[a] - dep[b];
	for (int i = 0; i <= 15; i++) {
		if ((t >> i) & 1) {
			addEdge(x, idp[a][i], INF);
			a = fa[a][i];
		}
	}
	for (int i = 15; i >= 0; i--) {
		if (fa[a][i] != fa[b][i]) {
			addEdge(x, idp[a][i], INF);
			addEdge(x, idp[b][i], INF);
			a = fa[a][i], b = fa[b][i];
		}
	}
	if (a != b) {
		addEdge(x, idp[a][0], INF);
		addEdge(x, idp[b][0], INF);
	}
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		ge[a].push_back({b, i});
		ge[b].push_back({a, i});
	}
	dfs(1, 0, 0);
	for (int i = 1, a, b; i <= m; i++) {
		scanf("%d %d", &a, &b);
		id[i] = ++tot;
		addEdge(S, id[i], 1);
		solve(a, b, id[i]);
	}
	for (int i = 2; i <= n; i++)
		addEdge(idm[i], T, 1);
	cout << dinic() << endl;
	vector<int> a, b;
	for (int i = 1; i <= m; i++) {
		if (layer[id[i]] == -1) a.push_back(i);
	}
	for (int i = 2; i <= n; i++) {
		if (layer[idm[i]] != -1) b.push_back(mm[i]);
	}
	cout << a.size();
	for (auto x : a) printf(" %d", x);
	cout << endl << b.size();
	for (auto x : b) printf(" %d", x);

	return 0;
}
