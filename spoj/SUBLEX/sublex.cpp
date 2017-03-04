#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 90005;

int cnt, last;
int tr[MAXN << 1][26], maxlen[MAXN << 1], slink[MAXN << 1];

void extend(int c) {
	int p = last;
	int np = last = ++cnt;
	maxlen[np] = maxlen[p] + 1;
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

void build(char *str) {
	int ll = strlen(str);
	for (int i = 0; i < ll; i++)
		extend(str[i] - 'a');
}

char a[MAXN];
long long sum[MAXN << 1];
vector<int> edges[MAXN << 1];
int deg[MAXN << 1];

int main() {
	freopen("sublex.in", "r", stdin);
	cnt = last = 1;
	scanf("%s", a);
	build(a);
	for (int i = 1; i <= cnt; i++) {
		for (int j = 0; j < 26; j++) {
			if (tr[i][j]) {
				deg[i]++;
				edges[tr[i][j]].push_back(i);
			}
		}
	}
	queue<int> q;
	for (int i = 1; i <= cnt; i++)
		if (!deg[i]) q.push(i);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		sum[p]++;
		for (auto fa : edges[p]) {
			sum[fa] += sum[p];
			if (!(--deg[fa])) q.push(fa);
		}
	}
	int n, x;
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &x);
		int p = 1;
		while (x) {
			for (int i = 0; i < 26; i++) {
				if (!tr[p][i]) continue;
				if (sum[tr[p][i]] >= x) {
					printf("%c", i + 'a');
					p = tr[p][i];
					x--;
					break;
				} else x -= sum[tr[p][i]];
			}
		}
		printf("\n");
	}

	return 0;
}
