#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#define INF 0x3f3f3f3f
#define MAXN 205
#define S 202
#define T 203

using namespace std;

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

int cas, n, m;
int arr[12];

bool check(int x) {
	for (int i = 0; i < n; i++)
		if (x & (1 << i))
			if (arr[i] < n - i - 1) return false;
	return true;
}

void rebuild(int x) {
	edges.clear();
	for (int i = 0; i <= T; i++)
		G[i].clear();
	for (int i = 0; i < n; i++)
		addEdge(S, i, arr[i]);
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			addEdge(i * n + j + n, T, 1);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			addEdge(i, i * n + j + n, 1);
			if ((!(x & (1 << i))) || arr[i] == arr[j]) {
				// if (x == 63) cout << i << ' ' << j << endl;
				addEdge(j, i * n + j + n, 1);

			}
		}
	}

}

int count(int x) {
	int ans = 0;
	while (x) {
		if (x & 1) ans++;
		x >>= 1;
	}
	return ans;
}

int main() {
	freopen("f.in", "r", stdin);
	scanf("%d\n", &cas);
	while (cas--) {
		string s;
		n = 0;
		getline(cin, s);
		int sum = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == ' ') continue;
			arr[n++] = s[i] - '0';
			sum += arr[n - 1];
		}
		m = (n * (n - 1)) / 2;
		int ans = 0;
		for (int i = 0; i < 1 << n; i++) {
			// if (!check(i)) continue;
			rebuild(i);
			int flow = dinic();
			if (flow == m) {
				ans = max(ans, count(i));
			}
		}
		cout << ans << endl;
	}


	return 0;
}
