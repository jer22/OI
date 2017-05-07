#include <bits/stdc++.h>

#define lowbit(x) ((x) & (-(x)))

using namespace std;

const int MAXN = 200005;

struct Node{
	int a, b, c, id;
	Node() {}
	Node(int e, int f, int g) : a(e), b(f), c(g) {}
	bool operator == (const Node &n) const {
		return a == n.a && b == n.b && c == n.c;
	}
};
bool cmp1(Node a, Node b) {
	if (a.a != b.a) return a.a < b.a;
	if (a.b != b.b) return a.b < b.b;
	return a.c < b.c;
}
bool cmp2(Node a, Node b) {
	return a.b < b.b;
}

int n, K;
int c[MAXN];
void insert(int p, int v) {
	for (int i = p; i <= K; i += lowbit(i))
		c[i] += v;
}
int getsum(int p) {
	int ans = 0;
	for (int i = p; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

int ans[MAXN];
Node arr[MAXN];
Node ll[MAXN], rr[MAXN];
vector<int> buff;
void solve(int l, int r) {
	if (l >= r) return;
	int mid = l + r >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	int siza = 0, sizb = 0;
	for (int i = l; i <= mid; i++)
		ll[++siza] = arr[i];
	for (int i = mid + 1; i <= r; i++)
		rr[++sizb] = arr[i];
	sort(ll + 1, ll + siza + 1, cmp2);
	sort(rr + 1, rr + sizb + 1, cmp2);
	int pa = 1, pb = 1;
	for (; pb <= sizb; ans[rr[pb].id] += getsum(rr[pb].c), ++pb) {
		for (; pa <= siza && ll[pa].b <= rr[pb].b; insert(ll[pa].c, 1), buff.push_back(ll[pa].c), ++pa);
	}
	for (int i = 0; i < buff.size(); i++)
		insert(buff[i], -1);
	buff.clear();
}

int cnt[MAXN];
int main() {
	freopen("3262.in", "r", stdin);
	scanf("%d %d", &n, &K);
	for (int i = 1, a, b, c; i <= n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		arr[i] = Node(a, b, c);
	}
	sort(arr + 1, arr + n + 1, cmp1);
	for (int i = 1; i <= n; i++)
		arr[i].id = i;
	solve(1, n);
	for (int i = n - 1; i >= 1; i--)
		if (arr[i] == arr[i + 1]) ans[i] = max(ans[i], ans[i + 1]);
	for (int i = 1; i <= n; i++)
		++cnt[ans[i]];
	for (int i = 0; i < n; i++)
		printf("%d\n", cnt[i]);

	return 0;
}
