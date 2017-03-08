#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
int phi = 0;
long long M;

void init() {
	phi = M;
	int a = M;
	for(int i = 2; i * i <= a; i++){
		if (!(a % i)){
			phi = phi / i * (i - 1);
			while(!(a % i)) a /= i;
		}
	}
	if (a > 1) phi = phi / a * (a - 1);
}

long long power(long long a, long long b) {
	long long ans = 1;
	for (; b; b >>= 1, (a *= a) %= M)
		if (b & 1) (ans *= a) %= M;
	return ans;
}

struct Edge{ int to, v; };
int n;
vector<Edge> edges[MAXN];
long long nimabi[MAXN];
bool ban[MAXN];

int sz_down[MAXN];
void dfs(int x, int pre) {
	sz_down[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == pre) continue;
		if (ban[nex]) continue;
		dfs(nex, x);
		sz_down[x] += sz_down[nex];
	}
}
void dfs1(int x, int pre, int &max_num, int &idx, int root) {
	int cnt = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == pre) continue;
		if (ban[nex]) continue;
		dfs1(nex, x, max_num, idx, root);
		cnt = max(cnt, sz_down[nex]);
	}
	cnt = max(cnt, sz_down[root] - sz_down[x]);
	if (cnt < max_num) {
		max_num = cnt;
		idx = x;
	}
}
int getroot(int x) {
	int max_num = 0x3f3f3f3f, idx;
	dfs(x, x);
	dfs1(x, x, max_num, idx, x);
	return idx;
}

long long ans = 0;
map<long long, int> man, woman, tot;
void fuck(int x, int pre, long long dcome, int len) {
	tot[dcome]++;
	for (auto e : edges[x])
		if (e.to != pre && !ban[e.to]) fuck(e.to, x, (dcome + e.v * nimabi[len] % M) % M, len + 1);
}
void jasf(int x, int pre, long long dcome, int len) {
	tot[dcome]--;
	for (auto e : edges[x])
		if (e.to != pre && !ban[e.to]) jasf(e.to, x, (dcome + e.v * nimabi[len] % M) % M, len + 1);
}
void caonima(int x, int pre, long long dgo, int len) {
	long long p = dgo ? M - dgo : 0;
	if (p) {
		long long q = p * power(nimabi[len], phi - 1) % M;
		ans += tot[q];
	} else {
		ans += tot[0] + 1;
	}
	for (auto e : edges[x])
		if (e.to != pre && !ban[e.to]) caonima(e.to, x, (dgo * 10 % M + e.v) % M, len + 1);
}

void solve(int x) {
	for (auto e : edges[x]) if (!ban[e.to]) {
		fuck(e.to, x, e.v % M, 1);
	}
	ans += tot[0];
	for (auto e : edges[x]) if (!ban[e.to]) {
		jasf(e.to, x, e.v % M, 1);
		caonima(e.to, x, e.v % M, 1);
		fuck(e.to, x, e.v % M, 1);
	}
	ban[x] = 1;
	tot.clear();
	for (auto e : edges[x])
		if (!ban[e.to]) solve(getroot(e.to));
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d %lld", &n, &M);
	init();
	for (int i = 1, a, b, c; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[++a].push_back((Edge){++b, c});
		edges[b].push_back((Edge){a, c});
		// if (!(c % M)) ans++;
	}
	nimabi[0] = 1;
	for (int i = 1; i <= n; i++)
		nimabi[i] = nimabi[i - 1] * 10 % M;
	solve(getroot(1));
	printf("%lld\n", ans);

	return 0;
}
