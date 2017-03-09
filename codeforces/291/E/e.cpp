#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int P = 199009;

int n;
vector<int> edges[MAXN];
char ch[MAXN];
char s[MAXN], str[MAXN];
int len;
int nex[MAXN];
int ans = 0;
int ttt[MAXN][130];
void dfs(int x, int cur) {
	for (auto v : edges[x]) {
		int tmp = cur;
		if (~ttt[x][ch[v]]) tmp = ttt[x][ch[v]];
		else {
			while (tmp && ch[v] != str[tmp])
				tmp = nex[tmp];
			if (ch[v] == str[tmp]) tmp++;
			ttt[x][ch[v]] = tmp;
		}
		if (tmp == len) ans++;
		dfs(v, tmp);
	}
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	int m = n;
	memset(ttt, -1, sizeof(ttt));
	for (int i = 2, x; i <= n; i++) {
		scanf("%d", &x);
		scanf("%s", s);
		int l = strlen(s);
		for (int j = 0; j < l; j++) {
			int p = (j == l - 1) ? i : ++m;
			edges[x].push_back(p);
			ch[p] = s[j];
			x = p;
		}
	}
	scanf("%s", str);
	len = strlen(str);
	int cur = 0;
	for (int i = 2; i <= len; i++) {
		while (cur && str[cur] != str[i - 1])
			cur = nex[cur];
		if (str[cur] == str[i - 1])
			cur++;
		nex[i] = cur;
	}
	dfs(1, 0);
	printf("%d\n", ans);

	return 0;
}
