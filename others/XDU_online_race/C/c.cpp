#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int T;
int n, m, w;
int arr[10005];
vector<int> edges[10005];
bool vis[10005];

void dfs(int x) {
	if (vis[x]) return;
	vis[x] = 1;
	int sum = 0;
	bool flag = false;
	for (int i = 0; i < edges[x].size(); i++) {
		flag = true;
		int nex = edges[x][i];
		dfs(nex);
		sum += arr[nex];
	}
	if (!flag) return;
	arr[x] = min(arr[x], sum + w);
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &m, &w);
		int k, x;
		for (int i = 0; i < n; i++)
			edges[i].clear();
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &arr[i], &k);
			for (int j = 0; j < k; j++) {
				scanf("%d", &x);
				edges[i].push_back(x);
			}
		}
		for (int i = 0; i < n; i++)
			if (!vis[i]) dfs(i);
		int ans = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			ans += arr[x];
		}
		printf("%d\n", ans);
	}


	return 0;
}
