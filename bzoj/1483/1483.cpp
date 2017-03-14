#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int n, m;
int col[MAXN];
set<int> pos[MAXN];
int sho[MAXN];
int ans = 0;

void merg(int a, int b) {
	for (set<int>::iterator it = pos[a].begin(); it != pos[a].end(); it++) {
		if (col[*it - 1] == b) ans--;
		if (col[*it + 1] == b) ans--;
		pos[b].insert(*it);
	}
	for (set<int>::iterator it = pos[a].begin(); it != pos[a].end(); it++)
		col[*it] = b;
	pos[a].clear();
}
int main() {
	freopen("1483.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &col[i]);
		pos[col[i]].insert(i);
		if (col[i] != col[i - 1]) ans++;
		sho[col[i]] = col[i];
	}
	int op, a, b;
	while (m--) {
		scanf("%d", &op);
		if (op == 2) printf("%d\n", ans);
		else {
			scanf("%d %d", &a, &b);
			if (a == b) continue;
			if (pos[sho[a]].size() > pos[sho[b]].size())
				swap(sho[a], sho[b]);
			merg(sho[a], sho[b]);
		}
	}


	return 0;
}
