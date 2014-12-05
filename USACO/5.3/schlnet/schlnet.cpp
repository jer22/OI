/*
ID:shijiey1
LANG:C++
PROG:schlnet
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int V;
vector<int> edges[105];
stack<int> s;
int vis[105];
int dfn[105];
int low[105];
int cnt = 0;
int num = 0;
int color[105];
int tree[105][105];
int in[105];
int out[105];
void tarjan(int u) {
	s.push(u);
	vis[u] = 1;
	cnt++;
	dfn[u] = low[u] = cnt;

	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}

	if (low[u] == dfn[u]) {
		int t;
		num++;
		do {
			t = s.top();
			color[t] = num;
			s.pop();
			vis[t] = 0;
		} while (t != u);
	}

}

int main() {
	freopen("schlnet.in", "r", stdin);
	freopen("schlnet.out", "w", stdout);
	scanf("%d", &V);
	int t;
	for (int i = 1; i <= V; i++) {
		while(cin >> t) {
			if (!t) break;
			edges[i].push_back(t);
		}
	}
	for (int i = 1; i <= V; i++) {
		if (!dfn[i]) tarjan(i);
	}
	
	for (int i = 1; i <= V; i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			if (color[i] == color[edges[i][j]]) continue;
			if (tree[color[i]][color[edges[i][j]]]) continue;
			tree[color[i]][color[edges[i][j]]] = 1;
			in[color[edges[i][j]]]++;
			out[color[i]]++;
		}
	}
	if (num == 1) cout << 1 << endl << 0 << endl;
	else {
		int ans1 = 0, ans2 = 0;
		for (int i = 1; i <= num; i++) {
			if (!in[i]) ans1++;
			if (!out[i]) ans2++;
		}
		cout << ans1 << endl << max(ans1, ans2) << endl;
	}
	
	return 0;
}
