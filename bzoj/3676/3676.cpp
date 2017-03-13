#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 300005;

int n;
int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1][22];
int siz[MAXN << 1], pos[MAXN];

void extend(int c, int f) {
	int p = last;
	int np = last = ++cnt;
	pos[f] = np;
	siz[np] = 1;
	maxlen[np] = maxlen[p] + 1;
	while (!tr[p][c] && p) tr[p][c] = np, p = slink[p][0];
	if (!p) slink[np][0] = 1;
	else {
		int q = tr[p][c];
		if (maxlen[p] + 1 == maxlen[q]) slink[np][0] = q;
		else {
			int nq = ++cnt;
			maxlen[nq] = maxlen[p] + 1;
			memcpy(tr[nq], tr[q], sizeof(tr[q]));
			slink[nq][0] = slink[q][0];
			slink[np][0] = slink[q][0]= nq;
			while (tr[p][c] == q) tr[p][c] = nq, p = slink[p][0];
		}
	}
}
int tp[MAXN << 1], c[MAXN];
void top() {
	for (int i = 1; i <= cnt; i++) c[maxlen[i]]++;
	for (int i = 1; i <= n; i++) c[i] += c[i - 1];
	for (int i = cnt; i; i--) tp[c[maxlen[i]]--] = i;
	for (int i = cnt; i; i--) {
		int p = tp[i];
		siz[slink[p][0]] += siz[p];
		for (int j = 1; j <= 21; j++)
			slink[p][j] = slink[slink[p][j - 1]][j - 1];
	}
}
long long ans = 0;
void query(int a, int b) {
	int p = pos[b];
	for (int i = 21; i >= 0; i--)
		if (maxlen[slink[p][i]] >= b - a + 1) p = slink[p][i];
	// cout << slink[4][0] << endl;
	ans = max(ans, (long long)siz[p] * (b - a + 1));
}
char ss[MAXN << 1];
int p[MAXN << 1];
void manacher(char s[MAXN], int n) {
	ss[0] = '$', ss[1] = '#';
	for (int i = 1; i <= n; i++)
		ss[i << 1] = s[i], ss[i << 1 | 1] = '#';
	n = n << 1 | 1;
	int mx = 1, id = 1;
	for (int i = 1; i <= n; i++) {
		p[i] = min(p[id + id - i], mx - i);
		while (ss[i + p[i]] == ss[i - p[i]]) {
			p[i]++;
		}
		if (p[i] + i > mx) {
			mx = p[i] + i, id = i;
			int a = (i - p[i] + 2 >> 1);
			int b = (i + p[i] - 1 >> 1);
			if (a <= b)
				query(a, b);
		}
	}
}

void build(char *str, int len) {
	cnt = last = 1;
	for (int i = 0; i < len; i++)
		extend(str[i] - 'a', i + 1);
}

char a[MAXN], b[MAXN];
int main() {
	freopen("3676.in", "r", stdin);
	scanf("%s", a + 1);
	n = strlen(a + 1);
	build(a + 1, n);
	top();
	manacher(a, n);
	printf("%lld\n", ans);

	return 0;
}
