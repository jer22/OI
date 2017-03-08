#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Node{ int to, v; };

int n, k;
vector<Node> edges[MAXN];
int siz[MAXN], maxson[MAXN], deep[MAXN];
long long len[MAXN];

void dfspre(int x, int pre, int d) {
	deep[x] = d;
	siz[x] = 1;
	for (auto nex : edges[x]) if (nex.to != pre) {
		len[nex.to] = len[x] + nex.v;
		dfspre(nex.to, x, d + 1);
		siz[x] += siz[nex.to];
		if (siz[nex.to] > siz[maxson[x]])
			maxson[x] = nex.to;
	}
}

map<long long, int> dist, predist;
int ans = 0x3f3f3f3f;
void fuck(int x, int pre, int r) {
	if (dist.find(len[x]) == dist.end()) dist[len[x]] = deep[x];
	else dist[len[x]] = min(dist[len[x]], deep[x]);
	
	if (predist.find(k - len[x] + 2 * len[r]) != predist.end())
		ans = min(ans, dist[len[x]] + predist[k - len[x] + 2 * len[r]] - 2 * deep[r]);
	
	for (auto nex : edges[x])
		if (nex.to != pre) fuck(nex.to, x, r);
}
void refuck(int x, int pre) {
	if (predist.find(len[x]) != predist.end()) predist[len[x]] = min(predist[len[x]], dist[len[x]]);
	else predist[len[x]] = dist[len[x]];
	for (auto nex : edges[x])
		if (nex.to != pre) refuck(nex.to, x);
}
// void fuckyou(int x, int pre) {
// 	if (d <= k) {
// 		predist[d] = 0x3f3f3f3f;
// 	}
// 	for (auto nex : edges[x])
// 		if (nex.to != pre) fuckyou(nex.to, x, min(d + nex.v, 1000001ll));
// }

void dfs(int x, int pre, bool keep) {
	for (auto nex : edges[x])
		if (nex.to != pre && nex.to != maxson[x]) dfs(nex.to, x, 0);
	if (maxson[x]) dfs(maxson[x], x, 1);
	// if (x == 2) cout << (predist.begin() -> f) << endl;
	for (auto nex : edges[x]) if (nex.to != pre && nex.to != maxson[x]) {
		fuck(nex.to, x, x);
		refuck(nex.to, x);
		dist.clear();
	}
	if (predist.find(k + len[x]) != predist.end()) {
		ans = min(ans, predist[k + len[x]] - deep[x]);
	}
	if (!keep) predist.clear();
	else {
		if (predist.find(len[x]) != predist.end())
			predist[len[x]] = min(predist[len[x]], deep[x]);
		else predist[len[x]] = deep[x];
	}
}

int main() {
	freopen("race.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1, a, b, c; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[++a].push_back((Node){++b, c});
		edges[b].push_back((Node){a, c});
	}
	dist.clear();
	predist.clear();
	dfspre(1, 1, 1);
	dfs(1, 1, 0);
	if (ans == 0x3f3f3f3f) ans = -1;
	printf("%d\n", ans);

	return 0;
}
