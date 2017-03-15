#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n, m, k, kk;
vector<int> edges[MAXN];
bool vis[MAXN];
int ans[MAXN << 1];
int cnt = 0;
int t = 0;
void dfs(int x) {
	vis[x] = 1;
	ans[++cnt] = x;
	if (cnt == kk) {
		printf("%d", cnt);
		for (int i = 1; i <= cnt; i++)
			printf(" %d", ans[i]);
		printf("\n");
		cnt = 0;
		t++;
	}
	for (auto nex : edges[x]) if (!vis[nex]) {
		dfs(nex);
		ans[++cnt] = x;
		if (cnt == kk) {
			printf("%d", cnt);
			for (int i = 1; i <= cnt; i++)
				printf(" %d", ans[i]);
			printf("\n");
			cnt = 0;
			t++;
		}
	}
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	kk = n * 2 / k + int(bool(n * 2 % k));
	for (int i = 1, a, b; i <= m; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1);
	if (cnt) {
		printf("%d", cnt);
		for (int i = 1; i <= cnt; i++)
			printf(" %d", ans[i]);
		printf("\n");
		cnt = 0;
		t++;
	}
	for (int i = t + 1; i <= k; i++)
		printf("1 1\n");


	return 0;
}
