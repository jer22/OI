#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[205];
int mat[205];
int done[205];

void addEdge(int a, int b) {
	edges[a].push_back(b);
}

bool dfs(int k) {
	for (int i = 0; i < edges[k].size(); i++) {
		int j = edges[k][i];
		if(done[j]) continue;
		done[j] = 1;
		if (!mat[j] || dfs(mat[j])) {
			mat[j] = k;
			return true;
		}
	}
	return false;
}

int match() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (dfs(i)) ans++;
		memset(done, 0, sizeof(done));
	}
	return ans;
}

int main() {
	freopen("1274.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		memset(mat, 0, sizeof(mat));
		memset(done, 0, sizeof(done));
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		int a;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a);
			int b;
			for (int j = 1; j <= a; j++) {
				scanf("%d", &b);
				addEdge(i, b);
			}
		}
		int ans = match();
		printf("%d\n", ans);
	}
	return 0;
}
