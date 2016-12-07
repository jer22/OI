#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n;
int arr[MAXN][2];
vector<int> edges[MAXN];
bool vis[MAXN];
int col[MAXN];

void dfs(int x, int d) {
	vis[x] = 1;
	col[x] = d;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (vis[nex]) continue;
		dfs(nex, d ^ 3);
	}
}

int main() {
	freopen("e.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
		edges[(i << 1) - 1].push_back(i << 1);
		edges[i << 1].push_back((i << 1) - 1);
		edges[arr[i][0]].push_back(arr[i][1]);
		edges[arr[i][1]].push_back(arr[i][0]);
	}
	for (int i = 1; i <= n << 1; i++)
		if (!vis[i]) dfs(i, 1);
	for (int i = 1; i <= n; i++)
		cout << col[arr[i][0]] << ' ' << col[arr[i][1]] << endl;

	return 0;
}
