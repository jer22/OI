#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 2000005;
const int MOD = 1000000007;

	// int p, q, np, nq;
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

int n;
char a[MAXN >> 1];
long long sum[MAXN << 1];
int vali[MAXN << 1];
int deg[MAXN << 1];
int main() {
	freopen("1457.in", "r", stdin);
	scanf("%d", &n);
	cnt = last = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%s", a);
		int len = strlen(a);
		for (int i = 0; i < len; i++)
			extend(a[i] - '0');
		if (i != n) extend(10);
	}
	for (int i = 1; i <= cnt; i++)
		for (int j = 0; j <= 10; j++) deg[tr[i][j]]++;
	queue<int> q;
	vali[1] = 1;
	q.push(1);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		for (int j = 0; j <= 10; j++) {
			if (!tr[p][j]) continue;
			if (j < 10) {
				vali[tr[p][j]] += vali[p];
				(sum[tr[p][j]] += sum[p] * 10 + j * vali[p]) %= MOD;
			}
			if (!(--deg[tr[p][j]])) q.push(tr[p][j]);
		}
	}
	long long ans = 0;
	for (int i = 1; i <= cnt; i++)
		(ans += sum[i]) %= MOD;
	printf("%lld\n", ans);
	return 0;
}
