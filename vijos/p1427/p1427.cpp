#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int n, s, t;
vector<int> edges[10010];
int father[10010];
int childcnt[10010];
int vis[10010];
string name[10010];

int find(int p) {
	if (p == father[p]) return p;
	return find(father[p]);
}

int lca = 0;
int dfs(int i) {
	vis[i] = 1;
	for (int j = 0; j < edges[i].size(); j++) {
		int current = edges[i][j];
		if (!vis[current]) {
			dfs(current);
			father[current] = i;
		}
	}
	if (i == s && vis[t]) lca = find(t);
	if (i == t && vis[s]) lca = find(s);
	return 0;
}

int main() {
	freopen("p1427.in", "r", stdin);
	scanf("%d %d %d", &n, &s, &t);
	int a, b;
	string c;
	for (int i = 0; i <= n; i++) {
		father[i] = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		name[a] = c;
		edges[b].push_back(a);
		childcnt[b]++;
	}
	// 求最近公共祖先
	dfs(0);
	int len = 0;
	int ans = 0;
	for (int i = s; i != lca; i = father[i]) {
		int temp = name[i].size();
		len += temp;
		ans += childcnt[i];
	}
	for (int i = t; i != father[lca]; i = father[i]) {
		int temp = name[i].size();
		len += temp;
		ans += childcnt[i];
	}
	ans -= childcnt[s];
	if (lca != t) ans -= childcnt[t];
	printf("%d\n%d\n", len, ans);
	return 0;
}
