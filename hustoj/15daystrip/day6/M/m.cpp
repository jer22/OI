#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#define INF 0x3f3f3f3f
#define MAXN 2005
#define S 0
#define T 2003

using namespace std;

struct Edge{
	int to;
	int cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

struct String{
	string s;
	int val;
	int rank;
	bool vis;
	String() {}
	String(string a, int b) {
		rank = 0;
		s = a;
		val = b;
		vis = true;
	}
	bool operator < (const String &ss) const {
		return rank > ss.rank;
	}
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


int cas, n, m;
string arr[MAXN];
vector<String> pre;
vector<String> suf;

string tostring(int x) {
	string s = "00000000";
	for (int i = 7; i >= 0; i--) {
		s[i] = (x & 1) + '0';
		x >>= 1;
	}
	return s;
}

bool isp(string a, string b) {
	bool flag = true;
	for (int k = 0; k < a.size(); k++)
		if (a[k] != b[k])
			return false;
	return true;
}

bool vis[275];
int main() {
	freopen("m.in", "r", stdin);
	scanf("%d", &cas);
	// cin.sync_with_stdio(false);
	for (int csss = 1; csss <= cas; csss++) {
		scanf("%d %d", &n, &m);
		edges.clear();
		for (int i = 0; i <= T; i++)
			G[i].clear();
		pre.clear();
		suf.clear();
		int x;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			arr[i] = tostring(x);
			addEdge(i, i + n, INF);
		}
		char op[5];
		int c;
		string s;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < m; i++) {
			scanf("%s", op);
			cin >> s;
			scanf("%d", &c);
			if (op[0] == 'P') {
				pre.push_back(String(s, c));
			} else {
				reverse(s.begin(), s.end());
				suf.push_back(String(s, c));
			}
		}
		for (int i = 0; i < pre.size(); i++) {
			for (int j = 0; j < pre.size(); j++) {
				if (i == j) continue;
				if (pre[i].s.size() > pre[j].s.size()) continue;
				if (isp(pre[i].s, pre[j].s)) {
					pre[i].rank++;
					pre[j].vis = false;
				}
			}
		}
		sort(pre.begin(), pre.end());
		for (int i = 0; i < pre.size(); i++) {
			if (!pre[i].rank) {
				for (int j = 1; j <= n; j++) {
					if (isp(pre[i].s, arr[j])) {
						addEdge(n * 2 + i + 1, j, INF);
						vis[j] = 1;
					}
				}
			} else {
				for (int j = i + 1; j < pre.size(); j++) {
					if (isp(pre[i].s, pre[j].s)) {
						addEdge(n + 2 + i + 1, n * 2 + j + 1, pre[j].val);
						break;
					}
				}
			}
			if (pre[i].vis) {
				addEdge(S, n * 2 + i + 1, pre[i].val);
			}
		}

		for (int i = 0; i < suf.size(); i++) {
			for (int j = 0; j < suf.size(); j++) {
				if (i == j) continue;
				if (suf[i].s.size() > suf[j].s.size()) continue;
				if (isp(suf[i].s, suf[j].s)) {
					suf[i].rank++;
					suf[j].vis = false;
				}
			}
		}
		sort(suf.begin(), suf.end());
		for (int i = 0; i < suf.size(); i++) {
			if (!suf[i].rank) {
				for (int j = 1; j <= n; j++) {
					string s = arr[j];
					reverse(s.begin(), s.end());
					if (isp(suf[i].s, s)) {
						addEdge(n + j, n * 2 + 500 + i + 1, INF);
						vis[j] = 1;
					}
				}
			} else {
				for (int j = i + 1; j < suf.size(); j++) {
					if (isp(suf[i].s, suf[j].s)) {
						addEdge(n * 2 + 500 + j + 1, n * 2 + 500 + i + 1, suf[j].val);
						break;
					}
				}
			}
			if (suf[i].vis) {
				addEdge(n * 2 + 500 + i + 1, T, suf[i].val);
			}
		}
		bool flag = false;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				printf("Case #%d: -1\n", csss);
				flag = true;
				break;
			}

		}
		if (!flag)
			printf("Case #%d: %d\n", csss, dinic());
	}



	return 0;
}
