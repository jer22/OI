#include <bits/stdc++.h>

using namespace std;

const double eps = 3e-4;
const int MAXN = 805;

struct E{
	int to, t, s;
	E() {}
	E(int a, int b, int c) : to(a), t(b), s(c) {}
};

struct Edge{
	int to;
	double cap;
	Edge() {}
	Edge(int a, double b) : to(a), cap(b) {}
};

vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];
int S, T;
void addEdge(int from, int to, double cap) {
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
			if ((layer[e.to] == -1) && (e.cap > eps)) {
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

double find(int x, double a) {
	if (x == T || fabs(a) < eps) return a;
	double flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (fabs(f = find(e.to, min(a, e.cap)))) > eps) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			a -= f;
			if (fabs(a) < eps) break;
		}
	}
	return flow;
}

double dinic() {
	double flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(S, 1e8);
	}
	return flow;
}


int n, m, nn, mm;
vector<E> es[705];

double dist[705];
bool vis[705];
queue<int> q;

double p(E e, double ans) { return (double)e.t - ans * (double)e.s; }
bool spfa(int s, double ans) {
	while (!q.empty()) q.pop();
	for (int i = 1; i <= n; i++)
		dist[i] = 1e8;

	q.push(s);
	dist[s] = 0.0;
	vis[s] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < es[current].size(); i++) {
			E e = es[current][i];
			if (dist[current] + p(e, ans) < dist[e.to]) {
				dist[e.to] = dist[current] + p(e, ans);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
	}
	return dist[n] < eps;
}

double val[705];
int main() {
	freopen("2285.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b, c, d;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		es[b].push_back(E(a, c, d));
	}
	scanf("%d %d", &mm, &nn);
	for (int i = 1; i <= nn; i++) {
		double l = 0, r = 100.0;
		while (l + eps < r) {
			double mid = (l + r) / 2.0;
			if (spfa(i, mid)) r = mid;
			else l = mid;
		}
		if (fabs(dist[n] - 1e8) < eps) val[i] = 1e8;
		else val[i] = (l + r) / 2.0;
	}
	S = nn + 1;
	T = nn + 2;
	for (int i = 0; i < mm; i++) {
		scanf("%d %d", &a, &b);
		if (fabs(val[a] - 1e8) < eps && fabs(val[b] - 1e8) < eps) {
			printf("-1\n");
			return 0;
		}
		addEdge(a, b, 1e8);
	}
	for (int i = 1; i <= nn; i++) {
		// cout << val[i] << endl;
		if (i & 1) addEdge(S, i, val[i]);
		else addEdge(i, T, val[i]);
	}
	double ans = dinic();
	printf("%.1lf\n", ans);

	return 0;
}
