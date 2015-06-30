#include <bits/stdc++.h>

#define pii pair<long long, long long>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 200005;

struct Node{
	long long l, r;
	int id;
	Node() {}
	Node(long long a, long long b, int c) : l(a), r(b), id(c) {}
	bool operator < (const Node &n) {
		if (l != n.l) return l < n.l;
		if (r != n.r) r < n.r;
		return id < n.id;
	}
};

int n, m;
long long l[MAXN], r[MAXN];
multiset<pii >s;
Node arr[MAXN];
int ans[MAXN];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		scanf("%I64d %I64d", &l[i], &r[i]);
	for (int i = 0; i < n - 1; i++)
		arr[i] = Node(r[i + 1] - l[i], l[i + 1] - r[i], i);
	sort(arr, arr + n - 1);
	long long t;
	for (int i = 0; i < m; i++) {
		scanf("%I64d", &t);
		s.insert(mp(t, i));
	}
	for (int i = 0; i < n - 1; i++) {
		set<pii >::iterator it = s.lower_bound(mp(arr[i].r, -1));
		if (it == s.end() || it -> first > arr[i].l) {
			cout << "No" << endl;
			return 0;
		}
		ans[arr[i].id] = it -> second;
		s.erase(it);
	}
	cout << "Yes" << endl;
	for (int i = 0; i < n - 1; i++)
		cout << ans[i] + 1 << " \n"[i == n - 2];

	return 0;
}
