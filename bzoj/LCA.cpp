#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXV 500
#define MAXE 1000

using namespace std;

/**
	输入数据是一个图
	储存图的边
*/
struct Gragh_Edge {
	int from;
	int to;
	int value;
	void add(int a, int b, int c) {
		from = a;
		to = b;
		value = c;
	}
	bool operator < (const Gragh_Edge &e) const {
		return value < e.value;
	}
};

struct Tree_Node {
	int to;
	int value;
};

int V, E;
int Q;
int size = 0;
int parent[MAXV];
Gragh_Edge gragh[MAXV];
vector<Tree_Node> tree[MAXV];
vector<int> query[MAXV];
int ans[MAXV][MAXV];
int father[MAXV];
int vis[MAXV];

int find(int r) {
	if (r == father[r]) return r;
	else return find(father[r]);
}

int find_parent(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find_parent(parent[p]); 
}

int un(int p, int q) {
	int rp = find_parent(p);
	int rq = find_parent(q);
	if (rp == rq)
		return 0;
	parent[rp] = q;
	return 1;
}

int dfs(int i) {
	vis[i] = 1;
	for (int j = 0; j < tree[i].size(); j++) {
		Tree_Node e = tree[i][j];
		if (!vis[e.to]) {
			dfs(e.to);
			father[e.to] = i;
		}
	}
	for (int j = 0; j < query[i].size(); j++) {
		int t = query[i][j];
		if (vis[t]) {
			ans[i][t] = ans[t][i] = find(t);
		}
	}
	return 0;
}

int main() {
	scanf("%d %d", &V, &E);
	for (int i = 0; i <= V; i++) {
		father[i] = i;
		parent[i] = i;
	}
	int x, y, z;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &x, &y, &z);
		gragh[size++].add(x, y, z);
	}
	printf("\n");
	// 最大生成树
	sort(gragh, gragh + size);
	for (int i = 0; i < E; i++) {
		Gragh_Edge g = gragh[i];
		if (find_parent(g.from) != find_parent(g.to)) {
			Tree_Node e;
			e.value = gragh[i].value;
			e.to = gragh[i].to;
			tree[gragh[i].from].push_back(e);
			e.to = gragh[i].from;
			tree[gragh[i].to].push_back(e);
			un(g.from, g.to);
		}
	}
	printf("\n");
	for (int i = 1; i <= V; i++) {
		for (int j = 0; j < tree[i].size(); j++) {
			printf("%d %d %d\n", i, tree[i][j].to, tree[i][j].value);
		}
	}
	printf("\n");
	scanf("%d", &Q);
	int a, b;
	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &a, &b);
		query[a].push_back(b);
		query[b].push_back(a);
	}

	dfs(1);
	for (int i = 0; i <= V; i++) {
		for (int j = 0; j < query[i].size(); j++) {
			int t = query[i][j];
			printf("%d %d %d\n", i, t, ans[i][t]);
		}
	}

	return 0;
}
