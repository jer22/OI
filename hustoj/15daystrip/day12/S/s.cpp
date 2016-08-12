#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define S 0
#define T 1003

using namespace std;

const int MOD = 20090717;
const int INF = 0x3f3f3f3f;

struct Edge{
	int to;
	long long cap;
	Edge() {}
	Edge(int a, long long b) : to(a), cap(b) {}
};

vector<Edge> edges;
vector<int> G[1005];
int layer[1005];
int cur[1005];

void add_edges(int from, int to, long long cap) {
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


int n, m, k, tot, root;
int nex[10005][26], fail[10005], val[10005], id[10005];
int lo[155], ha[155];
void insert(char str[], int idd) {
	int len = strlen(str);
	int pos = root;
	for (int i = 0; i < len; i++) {
		int t = str[i] - 'a';
		if (!nex[pos][t])
			nex[pos][t] = ++tot;
		pos = nex[pos][t];
	}
	val[pos] = lo[idd];
	id[pos] = idd + 1;
}

void build_fail() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		val[p] += val[fail[p]];
		int t;
		for (int i = 0; i < 26; i++) {
			if (!(t = nex[p][i]))
				nex[p][i] = nex[fail[p]][i];
			else {
				fail[t] = p ? nex[fail[p]][i] : 0;
				q.push(t);
			}
		}
	}
}


bool vis[10005];
vector<int> mat;
int query(char *str) {
	int ans = 0;
	int len = strlen(str);
	int pos = root;
	mat.clear();
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < len; i++) {
		int idx = str[i] - 'a';
		// while (!nex[pos][idx] && pos != root)
		// 	pos = fail[pos];
		pos = nex[pos][idx];
		int t = pos;
		// cout << val[t] << endl;
		// while (temp != root && temp -> cnt != -1) {
		// 	ans += temp -> cnt;
		// 	temp -> cnt = -1;
		// 	temp = temp -> fail;
		// }
		ans += val[t];
		while (t && !vis[t]) {
			if (id[t]) mat.push_back(id[t]);
			vis[t] = 1;
			t = fail[t];
		}
	}

	return ans;
}

int cas;
int main() {
	freopen("s.in", "r", stdin);
	scanf("%d", &cas);
	int cc = 0;
	while (cas--) {
		cc++;
		for (int i = 0; i <= T; i++)
			G[i].clear();
		edges.clear();

		scanf("%d %d", &n, &m);
		char str[1005];
		tot = 1;
		root = 0;
		memset(nex, 0, sizeof(nex));
		memset(id, 0, sizeof(id));
		memset(val, 0, sizeof(val));
		int tot = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &lo[i], &ha[i]);
			scanf("%s", str);
			insert(str, i);
			add_edges(i + m + 1, T, ha[i]);
		}
		build_fail();
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			int val = query(str);
			add_edges(S, i + 1, val);
			tot += val;
			for (int j = 0; j < mat.size(); j++) {
				// cout << mat[j] << ' ';
				add_edges(i + 1, mat[j] + m, INF);
			}
			// cout << val << endl;
		}
		int ans = tot - dinic();
		printf("Case %d: %d\n", cc, ans);
	}
	return 0;
}
