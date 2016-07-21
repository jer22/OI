#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> edges[200005];
int p[200005];
// int tag[200005];
int color[200005], num = 0;
int vis[200005];
int f[200005];

int dfs(int x, int pre) {
	int cnt = 0;
	if (x == p[x]) cnt++;

	vis[x] = 1;
	color[x] = num;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (vis[nex]) {
			if (nex != pre && !f[num]) {
				f[num] = x;
			}
			continue;
		}
		cnt += dfs(nex, x);
	}
	return cnt;
}

int main() {
	// freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
		if (i == p[i]) continue;
		edges[i].push_back(p[i]);
		edges[p[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		if (color[i]) continue;
		num++;
		if (i == p[i]) {
			color[i] = num;
			continue;
		}
		int cnt = dfs(i, i);
		// if (!cnt) tag[num] = 2;
		// else if (cnt == 1) tag[num] = 1;
		// else if (cnt > 1) while (1);
	}
	memset(vis, 0, sizeof(vis));
	int gp = 0;
	for (int i = 1; i <= n; i++) {
		if (i == p[i]) {
			gp = i;
			break;
		}
	}
	int ans = 0;
	if (!gp) {
		ans++;
		gp = f[color[1]];
		p[f[color[1]]] = f[color[1]];
		f[color[1]] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (i == gp) continue;
		if (vis[color[i]]) continue;
		// cout << i << endl;
		if (i == p[i]) {
			p[i] = gp;
			ans++;
			// cout << ans << endl;
		} else {
			if (!f[color[i]]) {
				if (p[i] != i) continue;
				p[i] = gp;
				ans++;
			} else {

				p[f[color[i]]] = gp;
				ans++;
			}
		}
		vis[color[i]] = 1;

	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++) {
		if (i != 1) printf(" ");
		printf("%d", p[i]);
	}
	printf("\n");

	return 0;
}
