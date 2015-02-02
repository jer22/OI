#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXV 100

using namespace std;

int V, E; // 二分图的每一侧各V个节点，节点编号1~V
vector<int> edges[MAXV];
int mat[MAXV]; // mat[i] = j：与右侧节点i匹配的左侧节点为j
int vis[MAXV];

bool dfs(int k) { // k为左侧的节点
	for (int i = 0; i < edges[k].size(); i++) {
		int j = edges[k][i];
		if (!vis[j]) {
			vis[j] = 1;
			if (!mat[j] || dfs(mat[j])) {
				mat[j] = k;
				return true;
			}
		}
	}
	return false;
}

int match() {
	int ans = 0;
	for (int i = 1; i <= V; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

int main() {
	scanf("%d %d", &V, &E);
	int a, b;
	for (int i = 0; i < E; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
	}
	int ans = match();
	printf("%d\n", ans);
	return 0;
}
