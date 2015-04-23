#include <bits/stdc++.h>

using namespace std;

const int MOD = 45989;

struct Edge{
	int from, to;
	Edge() {}
	Edge(int a, int b) : from(a), to(b) {}
};

struct Mar{
	int arr[200][200];
	Mar() { memset(arr, 0, sizeof(arr)); }
};

int n, m, k, S, T, cnt = 1;
vector<int> edges[25];
vector<Edge> e;

Mar operator * (Mar a, Mar b) {
	Mar c;
	for (int i = 1; i <= cnt; i++)
		for (int j = 1; j <= cnt; j++)
			for (int k = 1; k <= cnt; k++)
				c.arr[i][j] = (c.arr[i][j] + a.arr[i][k] * b.arr[k][j]) % MOD;
	return c;
}

Mar operator ^ (Mar a, int b) {
	Mar c;
	for (int i = 1; i <= cnt; i++)
		c.arr[i][i] = 1;
	while (b) {
		if (b & 1) c = c * a;
		a = a * a;
		b >>= 1;
	}
	return c;
}

int main() {
	freopen("1875.in", "r", stdin);
	scanf("%d %d %d %d %d", &n, &m, &k, &S, &T);
	int a, b;
	e.push_back(Edge(-1, -1));
	e.push_back(Edge(-1, -1));
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		e.push_back(Edge(a, b));
		e.push_back(Edge(b, a));
		cnt += 2;
		edges[a].push_back(cnt - 1);
		edges[b].push_back(cnt);
	}
	Mar ans, bns;
	for (int i = 0; i < edges[S].size(); i++)
		ans.arr[1][edges[S][i]]++;
	for (int i = 2; i <= cnt; i++)
		for (int j = 2; j <= cnt; j++)
			if (e[i].to == e[j].from)
				if (i != (j ^ 1)) bns.arr[i][j]++;
	ans = ans * (bns ^ (k - 1));
	int tot = 0;
	for (int i = 0; i < edges[T].size(); i++) {
		tot += ans.arr[1][edges[T][i] ^ 1];
		tot %= MOD;
	}
	cout << tot % MOD << endl;
	return 0;
}
