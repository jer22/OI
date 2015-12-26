#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;

const int MAXN = 500005;

int T, n, K, A, B;
int fa[MAXN];
vector<int> edges[MAXN];

int down[MAXN][12];
int up[MAXN][12];
void dfs_down(int x) {
	for (int i = 0; i <= K; i++)
		down[x][i] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == fa[x]) continue;
		dfs_down(nex);
		for (int j = 1; j <= K; j++) {
			down[x][j] += down[nex][j - 1];
		}
	}
}

void dfs_up(int x) {
	if (x != 1) {
		up[x][1] = 1;
		for (int i = 2; i <= K; i++) {
			up[x][i] = up[fa[x]][i - 1] + down[fa[x]][i - 1] - down[x][i - 2];
		}
	}
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == fa[i]) continue;
		dfs_up(nex);
	}
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d", &n, &K, &A, &B);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 2; i <= n; i++) {
			fa[i] = ((long long)A * (long long)i + (long long)B) % (i - 1) + 1;
			edges[fa[i]].push_back(i);
		}
		memset(down, 0, sizeof(down));
		dfs_down(1);
		memset(up, 0, sizeof(up));
		dfs_up(1);
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans ^= (up[i][K] + down[i][K]);
		cout << ans << endl;
	}


	return 0;
}
