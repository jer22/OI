#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1], minlen[MAXN << 1];

void extend(int c) {
	int p = last;
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
	while (!tr[p][c] && p) tr[p][c] = np, p = slink[p];
	if (!p) slink[np] = 1, minlen[np] = 1;
	else {
		int q = tr[p][c];
		if (maxlen[p] + 1 == maxlen[q]) slink[np] = q, minlen[np] = maxlen[q] + 1;
		else {
			int nq = ++cnt;
			maxlen[nq] = maxlen[p] + 1;
			memcpy(tr[nq], tr[q], sizeof(tr[q]));
			slink[nq] = slink[q];
			slink[np] = slink[q] = nq;
			minlen[np] = minlen[q] = maxlen[nq] + 1;
			while (tr[p][c] == q) tr[p][c] = nq, p = slink[p];
			minlen[nq] = maxlen[slink[nq]] + 1;
		}
	}
}

void build(char *str) {
	int ll = strlen(str);
	for (int i = 0; i < ll; i++)
		extend(str[i] - 'a');
}

bool vis[MAXN << 1];
long long ans = 0;
void dfs(int x) {
	vis[x] = 1;
	if (maxlen[x]) ans += maxlen[x] - minlen[x] + 1;
	for (int i = 0; i < 26; i++) {
		if (tr[x][i]) cout << x << ' ' << i << endl;
		if (tr[x][i] && !vis[tr[x][i]]) {
			dfs(tr[x][i]);
		}
	}
}

char a[MAXN];
int main() {
	freopen("1445.in", "r", stdin);
	scanf("%s", a);
	cnt = last = 1;
	build(a);
	dfs(1);
	cout << ans << endl;

	return 0;
}
