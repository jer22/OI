#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 100005;

int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1];

void extend(int c) {
	int p = last;
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
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

void build(char *str) {
	int ll = strlen(str);
	for (int i = 0; i < ll; i++)
		extend(str[i] - 'a');
}

char a[MAXN], b[MAXN];
int mi[MAXN << 1], tmp[MAXN << 1];
int deg[MAXN << 1];

int main() {
	freopen("lcs2.in", "r", stdin);
	scanf("%s", a);
	cnt = last = 1;
	build(a);
	for (int i = 1; i <= cnt; i++)
		mi[i] = maxlen[i];
	while (~scanf("%s", b)) {
		int len = strlen(b);
		int p = 1, l = 0;
		memset(tmp, 0, sizeof(tmp));
		for (int i = 0; i < len; i++) {
			int c = b[i] - 'a';
			while (p != 1 && !tr[p][c]) p = slink[p], l = maxlen[p];
			if (tr[p][c]) p = tr[p][c], l++;
			else p = 1, l = 0;
			tmp[p] = max(tmp[p], l);
		}

		queue<int> q;
		for (int i = 1; i <= cnt; i++)
			deg[slink[i]]++;
		for (int i = 1; i <= cnt; i++)
			if (!deg[i]) q.push(i);
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			mi[cur] = min(mi[cur], tmp[cur]);
			if (tmp[cur] && slink[cur]) tmp[slink[cur]] = maxlen[slink[cur]];
			if (!(--deg[slink[cur]])) q.push(slink[cur]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= cnt; i++)
		ans = max(ans, mi[i]);
	printf("%d\n", ans);


	return 0;
}
