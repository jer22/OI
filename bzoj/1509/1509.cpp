
/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m, root1, root2;
vector<Edge> edges[MAXN];
long long dis[MAXN];
int maxson[MAXN];

void dfs_root(int x, int pre) {
	dis[x] = maxson[x] = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		int nex = e.to;
		if (nex == pre) continue;
		dfs_root(nex, x);
		if (dis[nex] + e.v > dis[x]) {
			dis[x] = dis[nex] + e.v;
			maxson[x] = nex;
		}
	}
}

long long dist1[MAXN], dist2[MAXN];
void dfs_dist1(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		int nex = e.to;
		if (nex == pre) continue;
		dist1[nex] = dist1[x] + e.v;
		dfs_dist1(nex, x);
	}
}

void dfs_dist2(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		int nex = e.to;
		if (nex == pre) continue;
		dist2[nex] = dist2[x] + e.v;
		dfs_dist2(nex, x);
	}
}

int main() {
	freopen("1509.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	long long c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	dfs_root(1, 1);
	for (root1 = 1; maxson[root1]; root1 = maxson[root1]);
	dfs_root(root1, root1);
	for (root2 = root1; maxson[root2]; root2 = maxson[root2]);
	dfs_dist1(root1, root1);
	dfs_dist2(root2, root2);
	long long len = dist1[root2];
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, min(dist1[i], dist2[i]) + len);
	}
	printf("%lld\n", ans);

	return 0;
}
