#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXV 10010
#define MAXE 50010
#define MAXB 22
#define INF 0x3f3f3f3f

using namespace std;

// 输入数据的边
struct Edge {
	int from;
	int to;
	int value;
	bool operator < (const Edge &e) const {
		return value > e.value;
	}
};

// 生成树节点
struct TreeNode {
	int to;
	int value;
};

int V, E;
int Q;	// 询问个数
int parent[MAXV];	// 并查集
int size = 0;		// 生成树边的个数
Edge edges[MAXE];	// 输入数据
vector<TreeNode> tree[MAXV];	// 最大生成树

// 并查集操作
int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}
int un(int p, int q) {
	int tx = find(p);
	int ty = find(q);
	if (tx == ty)
		return 0;
	parent[tx] = q;
	return 1;
}


// father[i][j]:节点i的第2^j个祖先的编号
// father[i][j] = father[father[i][j - 1]][j - 1],
// 因为i的第2^j个祖先就等于i的第2^j-1个祖先的2^j-1个祖先
// 即2^j = 2^(j-1)+2^(j-1)
int father[MAXV][MAXB];
// minValue[i][j]:节点i到father[i][j]路径上的最小权值
// minValue[i][j] = min(minValue[i][j - 1], minValue[father[i][j - 1]][j - 1]);
int minValue[MAXV][MAXB];
int height[MAXV];	// height[i]:节点i在它所在的树上的深度
int visit[MAXV];	// dfs过程中某个点是否已被处理过

// 计算和r在同一棵树上的节点的高度，并计算father[i][0]和minValue[i][0]
// father[i][0]即i的第2^0个祖先节点，即i的父节点
void buildTree(int r) {
	visit[r] = 1;
	for (int i = 0; i < tree[r].size(); i++) {
		// 遍历r的每一个孩子结点
		TreeNode t = tree[r][i];
		if (!visit[t.to]) {
			father[t.to][0] = r;
			minValue[t.to][0] = t.value;
			height[t.to] = height[r] + 1;
			buildTree(t.to);
		}
	}
}

// 将节点a移动到高度为h的父节点
// 并计算路径上的最小权值
// a使用的是地址
int move(int &a, int h) {
	int res = INF;
	for (int i = MAXB - 1; i >= 0; i--) {
		// 每次将节点a向上移2^i个节点
		// 每次更新结果，直到深度即将小于h
		if (height[father[a][i]] >= h) {
			res = min(res, minValue[a][i]);
			a = father[a][i];
		}
	}
	return res;
}

// 查询两节点a和b之间的最小权值
int query(int a, int b) {
	int res = INF;
	if (height[a] != height[b]) {
		// 先将两节点高度调整至相等
		res = height[a] > height[b] ? move(a, height[b]) : move(b, height[a]);
	}
	if (a == b)
		return res;
	for (int i = MAXB - 1; i >= 0; i--) {
		// 每次将两节点同时向上移2^i个节点，直到两节点的"父节点"相等（重要）
		// 其中2^i为每次能移动的最长路径
		if (father[a][i] != father[b][i]) {
			// 计算两点分别所走的路径上的最小权值并更新结果
			res = min(res, min(minValue[a][i], minValue[b][i]));
			// 向上移动两节点
			a = father[a][i];
			b = father[b][i];
		}
	}
	// 此时两节点的父节点相等
	// 然后再考虑两节点到公共父节点的最小权值
	res = min(res, min(minValue[a][0], minValue[b][0]));
	return res;
}

int main() {
	freopen("1967.in", "r", stdin);
	scanf("%d %d", &V, &E);
	// 初始化并查集
	for (int i = 0; i <= V; i++) {
		parent[i] = i;
	}
	int u, v, l;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &u, &v, &l);
		Edge e;
		e.value = l;
		e.from = u;
		e.to = v;
		edges[size++] = e;
	}
	// 求最大生成树
	sort(edges, edges + size);
	for (int i = 0; i < size; i++) {
		Edge e = edges[i];
		if (find(e.from) != find(e.to)) {
			un(e.from, e.to);
			TreeNode t;
			t.value = e.value;
			t.to = e.to;
			tree[e.from].push_back(t);
			t.to = e.from;
			tree[e.to].push_back(t);
		}
	}

	memset(visit, 0, sizeof(visit));
	// 生成树可能是一片森林
	// 初始化节点在它所在的树上的高度，father[i][0]和minValue[i][0]
	for (int i = 1; i <= V; i++) {
		if (!visit[i]) {
			height[i] = 0;
			father[i][0] = i;
			minValue[i][0] = INF;
			buildTree(i);
		}
	}
	// 预处理出father[i][j]和minValue[i][j]
	for (int j = 1; j < MAXB; j++) {
		for (int i = 1; i <= V; i++) {
			father[i][j] = father[father[i][j - 1]][j - 1];
			minValue[i][j] = min(minValue[i][j - 1], minValue[father[i][j - 1]][j - 1]);
		}
	}
	int s, t;
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &s, &t);
		if (find(s) != find(t)) {
			printf("-1\n");
			continue;
		}
		printf("%d\n", query(s, t));
	}

	return 0;
}
