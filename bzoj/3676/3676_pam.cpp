#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

char s[MAXN];
int cnt, last = 0;
int tr[MAXN][27], fa[MAXN], len[MAXN], siz[MAXN];
void extend(int c, int n) {
	int p = last;
	while (s[n - len[p] - 1] != s[n]) p = fa[p];
	if (!tr[p][c]) {
		int now = ++cnt, k = fa[p];
		len[now] = len[p] + 2;
		while (s[n - len[k] - 1] != s[n]) k = fa[k];
		fa[now] = tr[k][c];
		tr[p][c] = now;
	}
	last = tr[p][c];
	siz[last]++;
}

void build(char *s, int n) {
	fa[0] = fa[1] = 1;
	cnt = 1;
	len[1] = -1;
	for (int i = 0; i < n; i++)
		extend(s[i] - 'a', i);
	for (int i = cnt; i; i--)
		siz[fa[i]] += siz[i];
}

int main() {
	freopen("3676.in", "r", stdin);
	scanf("%s", s);
	int n = strlen(s);
	build(s, n);
	long long ans = 0;
	for (int i = 1; i <= cnt; i++)
		ans = max(ans, (long long)siz[i] * len[i]);
	printf("%lld\n", ans);
	return 0;
}
