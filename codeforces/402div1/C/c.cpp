#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int n;
int tr[MAXN << 1][28];
int ans[MAXN], siz[MAXN];
int tot, cnt;
vector<pair<int, int> >del;

void fuck(int a, int b) {
	for (int i = 0; i < 26; i++) {
		if (!tr[b][i]) continue;
		if (tr[a][i]) {
			tot++;
		} else {
			tr[a][i] = ++cnt;
			del.push_back({a, i});
		}
		fuck(tr[a][i], tr[b][i]);
	}
}

void dfs(int x, int dep) {
	siz[x] = 1;
	int mxson = -1, mxsiz = 0;
	for (int i = 0; i < 26; i++) {
		if (!tr[x][i]) continue;
		dfs(tr[x][i], dep + 1);
		siz[x] += siz[tr[x][i]];
		if (siz[tr[x][i]] > mxsiz) {
			mxsiz = siz[tr[x][i]];
			mxson = i;
		}
	}
	if (mxson == -1) return;
	tot = 1;
	cnt = n;
	del.clear();
	for (int i = 0; i < 26; i++) {
		if (!tr[x][i]) continue;
		if (i == mxson) continue;
		tot++;
		fuck(tr[x][mxson], tr[x][i]);
	}
	for (auto p : del) {
		tr[p.first][p.second] = 0;
	}
	ans[dep] += tot;
	// cout << x << ' ' << tot << endl;
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	char c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %c", &a, &b, &c);
		tr[a][c - 'a'] = b;
	}
	dfs(1, 1);
	int d = 0, mx = 0;
	for (int i = 1; i <= n; i++) {
		if (ans[i] > mx) mx = ans[i], d = i;
	}
	cout << n - mx << endl << d << endl;


	return 0;
}
