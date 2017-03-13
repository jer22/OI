#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1];
int siz[MAXN << 1];

void extend(int c) {
	int p = last;
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
	siz[np] = 1;
	while (!tr[p][c] && p) tr[p][c] = np, p = slink[p];
	if (!p) slink[np] = 1;
	else {
		int q = tr[p][c];
		if (maxlen[p] + 1 == maxlen[q]) slink[np] = q;
		else {
			int nq = ++cnt;
			maxlen[nq] = maxlen[p] + 1;
			memcpy(tr[nq], tr[q], sizeof(tr[q]));
			slink[nq] = slink[q];
			slink[np] = slink[q] = nq;
			while (tr[p][c] == q) tr[p][c] = nq, p = slink[p];
		}
	}
}

int n;
char s[MAXN];
vector<int> edges[MAXN << 1];
long long ans = 0;

void dfs(int x) {
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		dfs(nex);
		ans -= (long long)siz[nex] * siz[x] * maxlen[x] * 2;
		siz[x] += siz[nex];
	}
}

int main() {
	freopen("3238.in", "r", stdin);
	scanf("%s", s);
	n = strlen(s);
	cnt = last = 1;
	for (int i = n - 1; i >= 0; i--)
		extend(s[i] - 'a');
	for (int i = 2; i <= cnt; i++)
		edges[slink[i]].push_back(i);
	ans = (long long)(n - 1) * n * (n + 1) / 2;
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}
