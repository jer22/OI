#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 1000005;

int cnt, last;
int siz[MAXN << 1];
int tr[MAXN << 1][27], maxlen[MAXN << 1], slink[MAXN << 1], minlen[MAXN << 1];

void extend(int c) {
	int p = last;
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
	siz[np] = 1;
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

int ans[MAXN];
int sum[MAXN << 1];

char str[MAXN];
int main() {
	freopen("nsubstr.in", "r", stdin);
	scanf("%s", str);
	cnt = last = 1;
	int n = strlen(str);
	for (int i = 0; i < n; i++)
		extend(str[i] - 'a');
	queue<int> q;
	for (int i = 1; i <= cnt; i++)
		sum[slink[i]]++;
	for (int i = 1; i <= cnt; i++)
		if (!sum[i]) q.push(i);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		siz[slink[cur]] += siz[cur];
		if (!(--sum[slink[cur]])) q.push(slink[cur]);
		ans[maxlen[cur]] = max(ans[maxlen[cur]], siz[cur]);
	}
	for (int i = n - 1; i >= 1; i--)
		ans[i] = max(ans[i], ans[i + 1]);
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);


	return 0;
}
