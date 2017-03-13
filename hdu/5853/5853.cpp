#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;

int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1];
int trie[MAXN << 1][26];
int id[MAXN << 1];
int extend(int p, int c) {
	int np = last = ++cnt;
	id[np] = np;
	maxlen[np] = maxlen[p] + 1;
	// trie[p][c] = np;
	while (!tr[p][c] && p) tr[p][c] = np, p = slink[p];
	if (!p) slink[np] = 1;
	else {
		int q = tr[p][c];
		if (maxlen[p] + 1 == maxlen[q]) slink[np] = q;
		else {
			int nq = ++cnt;
			id[nq] = np;
			maxlen[nq] = maxlen[p] + 1;
			memcpy(tr[nq], tr[q], sizeof(tr[q]));
			slink[nq] = slink[q];
			slink[np] = slink[q] = nq;
			while (tr[p][c] == q) tr[p][c] = nq, p = slink[p];
		}
	}
	return np;
}

int T, n, m;
char s[MAXN];

void dfs(int x, int p) {
	for (int i = 0; i < 26; i++) {
		if (!trie[x][i]) continue;
		int np = extend(p, i);
		dfs(trie[x][i], np);
	}
}
int main() {
	freopen("5853.in", "r", stdin);
	freopen("out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &m);
		memset(tr, 0, sizeof(tr));
		memset(trie, 0, sizeof(trie));
		cnt = last = 1;
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			int l = strlen(s);
			int p = 1;
			for (int i = 0; i < l; i++) {
				if (!trie[p][s[i] - 'a']) trie[p][s[i] - 'a'] = ++cnt, p = cnt;
				else p = trie[p][s[i] - 'a'];
			}
		}
		cnt = 1;
		dfs(1, 1);
		printf("Case #%d:\n", cas);
		// cout << cnt << endl;
		// cout << tr[1][3] << endl;
		for (int i = 0; i < m; i++) {
			scanf("%s", s);
			int p = 1, l = strlen(s);
			bool f = 0;
			for (int j = 0; j < l; j++) {
				int c = s[j] - 'a';
				if (!tr[p][c]) {
					printf("0\n");
					f = 1;
					break;
				}
				p = tr[p][c];
			}
			if (!f) printf("%d\n", maxlen[p] - maxlen[slink[p]]);
		}
	}

	return 0;
}
