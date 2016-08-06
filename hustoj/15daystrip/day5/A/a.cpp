#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 2005;

int n, m;
vector<int> edges[MAXN];
vector<int> tr[MAXN];
vector<int> tof[MAXN];
int dfn[MAXN], low[MAXN], vis[MAXN], dep[MAXN];
int nn[MAXN][MAXN];
int cnt = 0;
int bris = 0;
int num[MAXN], dp[MAXN];
long long ans = 0;

void makeTree(int x, int pre) {
	vis[x] = 1;
	dep[x] = dep[pre] + 1;
	
	bool flag = false;
	for (int j = 0; j < edges[x].size(); j++) {
		int nex = edges[x][j];
		if (nex == pre) {
			if (flag) tof[x].push_back(nex);
			flag = true;
		} else {
			if (!vis[nex]) {
				makeTree(nex, x);
				tr[x].push_back(nex);
			} else {
				if (dep[nex] > dep[x]) continue;
				tof[x].push_back(nex);
			}
		}
	}
}

int tag[MAXN];
void update(int x, int pre, int dpx, int depx) {
	vis[x] = 1;
	for (int j = 0; j < tr[x].size(); j++) {
		int nex = tr[x][j];
		if (vis[nex]) continue;
		// if (x == 2) cout << low[3] << endl;
		if (nn[nex][x] == 1 && dp[nex] == dpx && low[nex] < depx) {
			ans++;
		}
		update(nex, x, dpx, depx);
	}
}


void dfs(int x, int pre) {
	low[x] = dep[x];
	// tag[cnt] = dep[x];
	int cur = 0;
	for (int j = 0; j < tr[x].size(); j++) {
		int nex = tr[x][j];
		dfs(nex, x);
		low[x] = min(low[x], low[nex]);
		cur += dp[nex];
	}
	for (int j = 0; j < tof[x].size(); j++) {
		int nex = tof[x][j];
		low[x] = min(low[x], dep[nex]);
	}
	cur -= num[x];
	for (int j = 0; j < tof[x].size(); j++) {
		int nex = tof[x][j];
		num[nex]++;
		cur++;
	}
	dp[x] = cur;
	if (dp[x] == 1) ans++;
	if (x != 1){
		if (!dp[x]) bris++;
		if (dp[x] > 0 && nn[x][pre] == 1) {
			memset(vis, 0, sizeof(vis));
			update(x, pre, dp[x], dep[x]);
		}
	}

}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
		nn[a][b]++;
		nn[b][a]++;
	}
	makeTree(1, 1);
	memset(vis, 0, sizeof(vis));
	dfs(1, 1);
	ans += (long long)bris * (long long)(m - bris) + ((long long)bris * (long long)(bris - 1)) / 2ll;
	printf("%lld\n", ans);

	return 0;
}
