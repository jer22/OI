



int dfs(int u) {
	stack.push(u);
	vis[u] = 1;
	++cnt;
	low[u] = dfn[u] = cnt;
	for (int j = 0; j < lin[u].size(); j++) {
		int v = lin[u][j];
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		int t;
		num++;
		do {
			t = stack.top();
			col[t] = num;
			stack.pop();
			vis[t] = 0;
		}
		while (t != u);
	}
}