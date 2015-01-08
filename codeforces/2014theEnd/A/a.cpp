#include <bits/stdc++.h>

using namespace std;

int n, k;
int arr[30005];
int vis[30005];
int ans = false;
void dfs(int i) {
	vis[i] = 1;
	int nex = i + arr[i];
	if (nex == k) {
		printf("YES");
		exit(0);
	}
	if (vis[nex]) {
		printf("NO");
		exit(0);
	}
	dfs(nex);
}

int main() {
	while (~scanf("%d %d", &n, &k)) {
		for (int i = 1; i < n; i++)
			scanf("%d", &arr[i]);
		memset(vis, 0, sizeof(vis));
		dfs(1);
	}
	return 0;
}
