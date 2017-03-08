#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int n;
vector<int> edges[MAXN];
char ch[MAXN];
int siz[MAXN], son[MAXN], deep[MAXN], msk[MAXN];

void dfspre(int x, int d, int stat) {
	siz[x] = 1;
	deep[x] = d;
	msk[x] = stat;
	for (auto nex : edges[x]) {
		dfspre(nex, d + 1, stat ^ (1 << ch[nex] - 'a'));
		siz[x] += siz[nex];
		if (siz[nex] > siz[son[x]])
			son[x] = nex;
	}
}

int len[MAXN * 10];
int tmp = 0;
void fuck(int x, int r) {
	if (len[msk[x]]) tmp = max(tmp, len[msk[x]] + deep[x] - deep[r] * 2);
	for (int i = 0; i <= 21; i++) {
		if (len[msk[x] ^ (1 << i)]) {
			tmp = max(tmp, len[msk[x] ^ (1 << i)] + deep[x] - deep[r] * 2);
			// if (r == 1) cout << len[msk[x] ^ (1 << i)] << endl;
		}
		// if (r == 1 && (len[msk[x] ^ (1 << i)] + deep[x] - deep[r] * 2 == 8)) cout << x << ' ' << (msk[x] ^ (1 << i)) << ' ' << len[msk[x] ^ (1 << i)] << endl;
	}

	for (auto nex : edges[x])
		fuck(nex, r);
}
void fklasdj(int x) {
	len[msk[x]] = max(len[msk[x]], deep[x]);
	for (auto nex : edges[x])
		fklasdj(nex);
}
void wreiou(int x) {
	len[msk[x]] = 0;
	for (auto nex : edges[x])
		wreiou(nex);	
}
int ans[MAXN];
void dfs(int x, bool keep) {
	for (auto nex : edges[x])
		if (nex != son[x]) dfs(nex, 0);
	if (son[x]) dfs(son[x], 1);
	ans[x] = ans[son[x]];
	tmp = 0;
	for (auto nex : edges[x]) if (nex != son[x]) {
		ans[x] = max(ans[x], ans[nex]);
		fuck(nex, x);
		fklasdj(nex);
	}
	tmp = max(tmp, len[msk[x]] - deep[x]);
	for (int i = 0; i <= 21; i++)
		tmp = max(tmp, len[msk[x] ^ (1 << i)] - deep[x]);
	len[msk[x]] = max(len[msk[x]], deep[x]);
	ans[x] = max(ans[x], tmp);
	if (!keep) wreiou(x);
}

int main() {
	freopen("f.in", "r", stdin);
	freopen("ans", "w", stdout);

	scanf("%d", &n);
	for (int i = 2, x; i <= n; i++) {
		scanf("%d ", &x);
		scanf("%c", &ch[i]);
		edges[x].push_back(i);
	}
	dfspre(1, 1, 0);
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);

	return 0;
}
