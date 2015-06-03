#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 100010;

int s[MAXN];
int lowbit(int x) {
	return x & -x;
}

void add(int x, int v) {
	while (x < MAXN) {
		s[x] += v;
		x += lowbit(x);
	}
}

int get(int x) {
	int ans = 0;
	while (x) {
		ans += s[x];
		x -= lowbit(x);
	}
	return ans;
}

int fa[MAXN], next[MAXN][26], fail[MAXN];
int tot = 0;

char str[MAXN];
int strmap[MAXN];
int strcnt = 0;

void init_trie() {
	int pos = 0, len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == 'B') {
			pos = fa[pos];
		} else if (str[i] == 'P') {
			strmap[++strcnt] = pos;
		} else if (str[i] >= 'a' && str[i] <= 'z') {
			int id = str[i] - 'a';
			if (!next[pos][id]) {
				next[pos][id] = ++tot;
				fa[tot] = pos;
			}
			pos = next[pos][id];
		}
	}
}

vector<int> edges[MAXN];
void build_fail() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		int t;
		for (int i = 0; i < 26; i++) {
			if (!(t = next[p][i])) {
				next[p][i] = next[fail[p]][i];
			} else {
				fail[t] = p ? next[fail[p]][i] : 0;
				q.push(t);
			}
		}
	}
}

int m;
vector< pii > query[MAXN];
int dfn[MAXN], siz[MAXN];
int ans[MAXN];
int cnt = 0;

void dfs(int x) {
	dfn[x] = ++cnt;
	siz[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		dfs(edges[x][i]);
		siz[x] += siz[edges[x][i]];
	}
}

void solve() {
	for (int i = 1; i <= tot; i++)
		edges[fail[i]].push_back(i);
	dfs(0);
	int len = strlen(str);
	int pos = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == 'B') {
			add(dfn[pos], -1);
			pos = fa[pos];
		} else if (str[i] == 'P') {
			for (int i = 0; i < query[pos].size(); i++) {
				pii temp = query[pos][i];
				int root = temp.first;
				int r = dfn[root];
				ans[temp.second] = get(r + siz[root] - 1) - get(r - 1);
			}
		} else if (str[i] >= 'a' && str[i] <= 'z') {
			pos = next[pos][str[i] - 'a'];
			add(dfn[pos], 1);
		}
	}
}

int main() {
	scanf("%s", str);
	
	init_trie();
	build_fail();

	scanf("%d", &m);
	int x, y;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &x, &y);
		query[strmap[y]].push_back(mp(strmap[x], i));
	}
	solve();

	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);

	return 0;
}
