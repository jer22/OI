#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
vector<int> edges[MAXN];
int arr[MAXN], siz[MAXN], maxson[MAXN];

void dfspre(int x, int pre) {
	siz[x] = 1;
	for (auto nex : edges[x]) if (nex != pre) {
		dfspre(nex, x);
		siz[x] += siz[nex];
		if (siz[nex] > siz[maxson[x]])
			maxson[x] = nex;
	}
}

map<int, int> now, last;
void fuck(int x, int pre) {
	now[arr[x]]++;
	for (auto nex : edges[x])
		if (nex != pre) fuck(nex, x);
}

long long ans = 0;
void dfs(int x, int pre, bool keep) {
	for (auto nex : edges[x])
		if (nex != pre && nex != maxson[x]) dfs(nex, x, 0);
	if (maxson[x]) dfs(maxson[x], x, 1);

	for (auto nex : edges[x]) if (nex != pre && nex != maxson[x]) {
		now.clear();
		fuck(nex, x);
		for (auto it = now.begin(); it != now.end(); it++) {
			if (arr[x] % (it -> first)) continue;
			ans += last[arr[x] / (it -> first)] * (it -> second);
		}
		for (auto it = now.begin(); it != now.end(); it++)
			last[it -> first] += (it -> second);
	}
	ans += last[1];
	if (!keep) last.clear();
	else last[arr[x]]++;
}

int main() {
	freopen("tgt.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	dfspre(1, 1);
	dfs(1, 1, 0);
	printf("%lld\n", ans);

	return 0;
}
