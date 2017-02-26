#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Node{
	int a, b;
	long long h;
	bool operator < (const Node &n) const {
		if (b != n.b) return b > n.b;
		if (a != n.a) return a > n.a;
		return h > n.h;
	}
};

int n;
Node arr[MAXN];
map<int, int> has;
long long c[MAXN];

void update(int pos, long long v) {
	for (int i = pos; i < MAXN; i += i & (-i))
		c[i] = max(c[i], v);
}

long long getans(int p) {
	long long res = 0;
	for (int i = p; i; i -= i & (-i))
		res = max(res, c[i]);
	return res;
}

int main() {
	freopen("e.in", "r", stdin);
	int a, b;
	long long c;
	set<int> st;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		arr[i] = (Node){a, b, c};
		st.insert(a);
		st.insert(b);
	}
	sort(arr + 1, arr + n + 1);
	int t = 1;
	for (auto i : st) has[i] = t++;
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		long long res = getans(has[arr[i].b] - 1) + arr[i].h;
		ans = max(ans, res);
		update(has[arr[i].a], res);
	}
	cout << ans << endl;

	return 0;
}
