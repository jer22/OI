#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 500005;

int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1];
long long sum[MAXN << 1], siz[MAXN << 1];
int T, k;

void extend(int c) {
	int p = last;
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
	if (T) siz[np] = 1;
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

int c[MAXN << 1], tp[MAXN << 1];
char a[MAXN];
int main() {
	freopen("3998.in", "r", stdin);
	scanf("%s", a + 1);
	scanf("%d %d", &T, &k);
	cnt = last = 1;
	int n = strlen(a + 1);
	for (int i = 1; i <= n; i++)
		extend(a[i] - 'a');
	for (int i = 1; i <= cnt; i++) c[maxlen[i]]++;
	for (int i = 1; i <= n; i++) c[i] += c[i - 1];
	for (int i = cnt; i >= 1; i--) tp[c[maxlen[i]]--] = i;
	for (int i = cnt; i >= 1; i--) {
		int p = tp[i];
		if (T) siz[slink[p]] += siz[p];
		else siz[p] = 1;
	}
	siz[1] = 0;
	for (int i = cnt; i >= 1; i--) {
		int p = tp[i];
		sum[p] = siz[p];
		for (int j = 0; j < 26; j++) if (tr[p][j])
			sum[p] += sum[tr[p][j]];
	}
	if (sum[1] < k) {
		printf("-1\n");
		return 0;
	}
	int p = 1;
	while (k) {
		if (k <= siz[p]) break;
		k -= siz[p];
		for (int i = 0; i < 26; i++) if (tr[p][i]) {
			if (k <= sum[tr[p][i]]) {
				p = tr[p][i];
				printf("%c", i + 'a');
				break;
			} else k -= sum[tr[p][i]];
		}

	}
	printf("\n");
	return 0;
}
