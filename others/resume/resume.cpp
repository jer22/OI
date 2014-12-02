#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int edges[55][55];
int vis[55];
int arr[55];
bool flag = false;

void addEdge(int a, int b) {
	edges[a][b] = 1;
	edges[b][a] = 1;
}

void print() {
	for (int i = 1; i <= n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int dfs(int step, int i) {
	if (flag) return 0;
	if (step == n) {
		if (edges[i][1]) {
			print();
			flag = true;
		}
		return 0;
	}
	for (int j = 1; j <= n; j++) {
		if (edges[i][j] && !vis[j]) {
			vis[j] = 1;
			arr[step + 1] = j;
			dfs(step + 1, j);
			vis[j] = 0;
			arr[step + 1] = 0;
		}
	}
}

int main() {
	freopen("resume.in", "r", stdin);
	freopen("resume.out", "w", stdout);
	scanf("%d", &n);
	int u, v;
	while (cin >> u >> v) {
		addEdge(u, v);
	}
	memset(vis, 0, sizeof(vis));
	vis[1] = 1;
	arr[1] = 1;
	dfs(1, 1);

	return 0;
}
