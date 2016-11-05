#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 400005;
const int MAXM = 1000005;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

struct Edge{
	int from, to, dii;
	Edge() {}
	Edge(int a, int b, int c = -1)
		: from(a), to(b), dii(c) {}
};

int T, n, m, s, t;
vector<Edge> edges;
vector<int> G[MAXN];
int deep[MAXN], fae[MAXN];
vector<int> rejs[MAXN];
bool vis[MAXN];
int lnk[MAXN];

void bfs() {
	for (int i = 1; i <= n; i++)
		vis[i] = 0;
	static queue<pii > q;
	q.push(mp(t, 1));
	vis[t] = 1;
	while (!q.empty()) {
		pii cur = q.front();
		q.pop();
		int x = cur.first;
		int dir = cur.second;

		edges[fae[x]].dii = dir;

		int nex = edges[fae[x]].from;
		for (int i = 0; i < rejs[x].size(); i++) {
			Edge &e = edges[rejs[x][i]];

			e.dii = dir;

			if (!vis[e.to]) {
				vis[e.to] = 1;
				q.push(mp(e.to, dir ^ 1));
			}
		}
		if (nex != s && !vis[nex]) {
			vis[nex] = 1;
			q.push(mp(nex, dir));
		}
	}
}

void dfs(int x, int pre) {
	for (int i = 0; i < G[x].size(); i++) {
		Edge e = edges[G[x][i]];
		if (e.to == pre) continue;
		if (deep[e.to]) {
			if (deep[e.to] < deep[x]) {
				rejs[lnk[e.to]].push_back(G[x][i] ^ 1);
			}
		}
		else {
			fae[e.to] = G[x][i];
			deep[e.to] = deep[x] + 1;
			lnk[x] = e.to;
			dfs(e.to, x);
		}
	}
}

int main() {
	// freopen("k.in", "r", stdin);
	T = read();
	while (T--) {
		n = read(), m = read(), s = read(), t = read();
		edges.clear();
		for (int i = 1; i <= n; i++) {
			G[i].clear();
			rejs[i].clear();
		}
		int a, b;
		for (int i = 1; i <= m; i++) {
			a = read(), b = read();
			edges.push_back(Edge(a, b));
			edges.push_back(Edge(b, a));
			G[a].push_back(edges.size() - 2);
			G[b].push_back(edges.size() - 1);
		}
		for (int i = 1; i <= n; i++) {
			deep[i] = fae[i] = lnk[i] = 0;
		}
		deep[s] = 1;
		dfs(s, s);
		bfs();
		bool flag = true;
		for (int i = 0; i < edges.size(); i += 2) {
			if (edges[i].dii == -1 && edges[i ^ 1].dii == -1) {
				flag = false;
				break;
			}
		}
		if (!flag) printf("No\n");
		else {
			printf("Yes\n");
			for (int i = 0; i < edges.size(); i += 2) {
				if (edges[i].dii == 1 || !edges[i ^ 1].dii) printf("%d %d\n", edges[i].from, edges[i].to);
				if (edges[i ^ 1].dii == 1 || !edges[i].dii) printf("%d %d\n", edges[i].to, edges[i].from);
			}
		}
	}
	return 0;
}
