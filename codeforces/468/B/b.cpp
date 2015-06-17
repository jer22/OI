#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n, a, b;
map<int, int> Hash;
int arr[100005];
vector<int> edges[MAXN];
int cnt = 0, num = 0;
int dfn[MAXN], low[MAXN], vis[MAXN], col[MAXN];
int tot = 0;

stack<int> s;
void dfs(int u) {
	s.push(u);
	vis[u] = 1;
	low[u] = dfn[u] = ++cnt;
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		int t;
		num++;
		do {
			t = s.top();
			s.pop();
			vis[t] = 0;
			col[t] = num;
		} while (t != u);
	}
}

bool tarjan() {
	for (int i = 1; i <= tot * 2; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= tot; i++) {
		if (col[i] == col[i + tot]) return false;
		// cout << col[i] << ' ' << col[i + tot] << endl;
	}
	return true;
}

int refl[MAXN];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> a >> b;
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		if (!Hash[arr[i]]) {
			Hash[arr[i]] = ++tot;
			refl[tot] = arr[i];
		}
	}
	for (int i = 1; i <= tot; i++) {
		int t = refl[i];
		int c = Hash[a - t], d = Hash[b - t];
		if (!c && !d) {
			printf("NO\n");
			return 0;
		}
		if (c) {
			// cout << c << ' ' << t << endl;
			edges[i].push_back(c);
			edges[c].push_back(i);
			edges[i + tot].push_back(c + tot);
			edges[c + tot].push_back(i + tot);
		} else {
			edges[i + tot].push_back(i);
		}
		if (d) {
			edges[i].push_back(d);
			edges[d].push_back(i);
			edges[i + tot].push_back(d + tot);
			edges[d + tot].push_back(i + tot);
		} else {
			edges[i].push_back(i + tot);
		}
	}
	if (!tarjan()) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	// int c = col[1];
	for (int i = 1; i <= n; i++) {
		int t = Hash[arr[i]];
		// cout << col[t] << ' ' << col[t + tot] << endl;
		if (col[t] > col[t + tot]) cout << '0';
		else cout << '1';
		cout << " \n"[i == n];
	}

	return 0;
}
