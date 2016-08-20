#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 2005;

int T;
char s[MAXN];
int last, cnt, ans;
int tr[MAXN << 1][27], len[MAXN << 1], fa[MAXN << 1];

void init() {
	cnt = last = 1;
	ans = 0;
	// memset(len, 0, sizeof(len));
	// memset(fa, 0, sizeof(fa));
	memset(tr, 0, sizeof(tr));
}

void extend(int c) {
	int p = last;
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
	ans += len[np] - len[fa[np]];
}

int ret[MAXN][MAXN];
int main() {
	freopen("j.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		for (int i = 0; i < strlen(s); i++) {
			init();
			for (int j = i; j < strlen(s); j++) {
				extend(s[j] - 'a');
				ret[i][j] = ans;
				// cout << ans << endl;
				// cout << s[j] << endl;
			}
		}
		// cout << ans << endl;
		// cout << ret[4][4];
		int q;
		scanf("%d", &q);
		int a, b;
		while (q--) {
			scanf("%d %d", &a, &b);
			printf("%d\n", ret[a - 1][b - 1]);
		}
	}




	return 0;
}
