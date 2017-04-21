#include <bits/stdc++.h>

#define lowbit(x) ((x) & (-(x)))
#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 100005;

struct Query{
	int n, m, k, id;
	Query() {}
	Query(int a, int b, int c, int d) : n(a), m(b), k(c), id(d) {}
	bool operator < (const Query &q) const {
		return k < q.k;
	}
};

int mob[MAXN];
int dsum[MAXN];
vector<pii > ds;
void getMob() {
	for (int i = 1; i <= 100000; ++i) {
		dsum[i] += i;
		ds.push_back(mp(dsum[i], i));
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= 100000; j += i) {
			mob[j] += delta;
			dsum[j] += (int)i;
		}
	}
}
int c[MAXN];
void insert(int p, int x) {
	for (int i = p; i <= 100000; i += lowbit(i))
		c[i] += x;
}
int getsum(int p) {
	int ans = 0;
	for (int i = p; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

vector<Query> querys;
int ans[MAXN];

int getans(int n, int m) {
	int ans = 0;
	for (int d = 1, pos; d <= n; d = pos + 1) {
		pos = min(n / (n / d), m / (m / d));
		ans += (n / d) * (m / d) * (getsum(pos) - getsum(d - 1));
	}
	return ans;
}

int main() {
	freopen("3529.in", "r", stdin);
	getMob();
	int T;
	scanf("%d", &T);
	for (int i = 1, n, m, k; i <= T; ++i) {
		scanf("%d %d %d", &n, &m, &k);
		if (n > m) swap(n, m);
		querys.push_back(Query(n, m, k, i));
	}
	sort(querys.begin(), querys.end());
	sort(ds.begin(), ds.end());
	ds.push_back(mp(0x3f3f3f3f, 0x3f3f3f3f));
	int idx = 0;
	for (int i = 0; i < T; ++i) {
		for (; ds[idx].first <= querys[i].k; ++idx) {
			for (int d = ds[idx].second; d <= 100000; d += ds[idx].second)
				insert(d, ds[idx].first * mob[d / ds[idx].second]);
		}
		ans[querys[i].id] = getans(querys[i].n, querys[i].m);
	}
	for (int i = 1; i <= T; ++i) {
		printf("%d\n", ans[i] & 2147483647);
	}
	return 0;
}
