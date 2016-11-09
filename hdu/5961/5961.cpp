#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2025;

int T, n;
vector<int> edges[2][MAXN];
char s[MAXN];
int vis[MAXN];

bool dfs(int x, int id) {
	vis[x] = -1;
	for (int i = 0; i < edges[id][x].size(); i++) {
		int nex = edges[id][x][i];
		if (vis[nex] == -1) return false;
		if (!vis[nex] && !dfs(nex, id)) return false;
	}
	vis[x] = 1;
	return true;
}

int main() {
	// freopen("5961.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			edges[0][i].clear();
			edges[1][i].clear();
		}
		for (int i = 1; i <= n; i++) {
			scanf("%s", s + 1);
			for (int j = 1; j <= n; j++) {
				if (s[j] == 'P') {
					edges[0][i].push_back(j);
					edges[1][i].push_back(j);
				} else if (s[j] == 'Q') {
					edges[0][i].push_back(j);
					edges[1][j].push_back(i);
				}
			}
		}
		memset(vis, 0, sizeof(vis));
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && !dfs(i, 0)) {
				flag = false;
				break;
			}
		}
		if (flag) {
			memset(vis, 0, sizeof(vis));
			for (int i = 1; i <= n; i++) {
				if (!vis[i] && !dfs(i, 1)) {
					flag = false;
					break;
				}
			}
		}
		cout << "NT"[(int)flag] << endl;
	}
	return 0;
}
