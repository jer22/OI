#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 100005;

	// int p, q, np, nq;
int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1], minlen[MAXN << 1];
int siz[MAXN << 1], deg[MAXN << 1];
void extend(int c) {
	int p = last;
	int np = last = ++cnt;
	siz[np] = 1;
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

char str[MAXN], s[MAXN << 1];
bool vis[MAXN << 1];
int solve() {
	int lens = strlen(s);
	int n = (lens >> 1) + 1;
	int p = 1, len = 0;
	int ans = 0;

	for (int i = 0; i < lens; i++) {
		int c = s[i] - 'a';
		while (p != 1 && !tr[p][c]) p = slink[p], len = maxlen[p];
		if (!tr[p][c]) p = 1, len = 0;
		else p = tr[p][c], len++;
		if (len > n) {
			while (maxlen[slink[p]] >= n) p = slink[p], len = maxlen[p];
		}
		if (len >= n && !vis[p]) {
			vis[p] = 1;
			ans += siz[p];
		}
	}

	return ans;
}

int main() {
	freopen("1465.in", "r", stdin);
	scanf("%s", str);
	cnt = last = 1;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		extend(str[i] - 'a');
	queue<int> q;
	for (int i = 1; i <= cnt; i++)
		deg[slink[i]]++;
	for (int i = 1; i <= cnt; i++)
		if (!deg[i]) q.push(i);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		siz[slink[p]] += siz[p];
		if (!(--deg[slink[p]])) q.push(slink[p]);
	}
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s);
		int lens = strlen(s);
		for (int i = 0; i < lens - 1; i++)
			s[lens + i] = s[i];
		s[(lens << 1) - 1] = '\0';
		for (int i = 1; i <= cnt; i++)
			vis[i] = 0;
		cout << solve() << endl;
	}



	return 0;
}
