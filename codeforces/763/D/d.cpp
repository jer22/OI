#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <cassert>

#define unsigned unsigned long long

using namespace std;

const int MAXN = 100005;
const unsigned P = 1000000007;

int n;
vector<int> edges[MAXN];
unsigned p[MAXN << 1];
int has[MAXN], tot = 0;

int root = 1;
map<unsigned, int> hases;
int cnt[MAXN << 1];
int num = 0;
int ans = 0;

void dfspre(int x, int pre) {
	unsigned ss = 0;
	for (auto nex : edges[x]) if (nex != pre)
		dfspre(nex, x), ss += p[has[nex]];
	if (!hases[ss]) hases[ss] = ++tot;
	has[x] = hases[ss];
	if (!cnt[has[x]]) num++;
	cnt[has[x]]++;
}


void dfs(int x, int fa, int out) {
	int siz = edges[x].size();
	cnt[has[x]]--;
	if (!cnt[has[x]]) num--;
	if (num + 1 > ans) ans = num + 1, root = x;
	unsigned ss = 0;
	for (auto nex : edges[x])
		if (nex != fa) ss += p[has[nex]];
	ss += p[out];
	for (auto nex : edges[x]) {
		if (nex == fa) continue;
		unsigned ns = ss - p[has[nex]];
		if (!hases[ns]) hases[ns] = ++tot;
		int qq = hases[ns];
		if (!cnt[qq]) num++;
		cnt[qq]++;
		// if (num > ans) ans = num, root = nex;
		dfs(nex, x, qq);
		cnt[qq]--;
		if (!cnt[qq]) num--;
	}
	if (!cnt[has[x]]) num++;
	cnt[has[x]]++;
	// if (num > ans) ans = num, root = x;
}
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n << 1; i++)
		p[i] = (1 + rand()) * 23333ll + (rand() * 7ll + 129873123ll) + ((rand() + 1243) << 30);
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfspre(1, 0);
	ans = 0;
	dfs(1, 0, 0);
	cout << root << endl;
	// cout << ans << endl;

	return 0;
}
