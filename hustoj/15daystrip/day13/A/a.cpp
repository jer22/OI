#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 250005;

	// int p, q, np, nq;
int cnt, last;
int tr[MAXN << 1][26], len[MAXN << 1], fa[MAXN << 1];

void extend(int c) {
	int p = last;;
	int np = last = ++cnt;
	len[np] = len[p] + 1;
	while (!tr[p][c] && p) tr[p][c] = np, p = fa[p];
	if (!p) fa[np] = 1;
	else {
		int q = tr[p][c];
		if (len[p] + 1 == len[q]) fa[np] = q;
		else {
			int nq = ++cnt;
			len[nq] = len[p] + 1;
			memcpy(tr[nq], tr[q], sizeof(tr[q]));
			fa[nq] = fa[q];
			fa[np] = fa[q] = nq;
			while (tr[p][c] == q) tr[p][c] = nq, p = fa[p];
		}
	}
}

void build(char *str) {
	int ll = strlen(str);
	for (int i = 0; i < ll; i++)
		extend(str[i] - 'a');
}

char a[MAXN], b[MAXN];
int main() {
	freopen("a.in", "r", stdin);
	scanf("%s", a);
	scanf("%s", b);
	cnt = last = 1;
	build(a);


	int now = 1;
	int ans = 0, temp = 0;
	for (int i = 0; i < strlen(b); i++) {
		int id = b[i] - 'a';
		if (tr[now][id]) {
			now = tr[now][id];
			temp++;
		} else {
			while (now && !tr[now][id]) now = fa[now];
			if (!now) {
				now = 1;
				temp = 0;
			} else {
				temp = len[now] + 1;
				now = tr[now][id];
			}
		}
		ans = max(ans, temp);
	}
	printf("%d\n", ans);



	return 0;
}
