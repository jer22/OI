/*
ID:shijiey1
PROG:stall4
LANG:C++
*/

/*
二分图匹配，匈牙利算法即可。
数据范围不大最大流也能过。
*/
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
	freopen("stall4.in", "r", stdin);
	freopen("stall4.out", "w", stdout);
	scanf("%d %d", &n, &m);
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
	return 0;
}
