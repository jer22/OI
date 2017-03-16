#include <bits/stdc++.h>

using namespace std;

struct Node{
	int dist, cnt;
	Node() {}
	Node(int a, int b) : dist(a), cnt(b) {}
	bool operator < (const Node &n) const {
		return dist < n.dist;
	}
};

int n, k;
vector<Node> a, b;
int main() {
	freopen("j.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1, c, d; i <= n; i++) {
		scanf("%d %d", &c, &d);
		if (c < 0) a.push_back(Node(abs(c), d));
		else b.push_back(Node(c, d));
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	long long ans = 0;
	int t = a.size() - 1;
	while (~t) {
		int kk = a[t].cnt / k;
		ans += 1ll * kk * a[t].dist * 2;
		a[t].cnt -= kk * k;
		if (!a[t].cnt) {
			t--;
			continue;
		}
		int now = k;
		ans += 1ll * a[t].dist * 2;
		while (now && ~t) {
			int mi = min(a[t].cnt, now);
			a[t].cnt -= mi;
			now -= mi;
			if (!a[t].cnt) t--;
		}
	}
	t = b.size() - 1;
	while (~t) {
		int kk = b[t].cnt / k;
		ans += 1ll * kk * b[t].dist * 2;
		b[t].cnt -= kk * k;
		if (!b[t].cnt) {
			t--;
			continue;
		}
		int now = k;
		ans += 1ll * b[t].dist * 2;
		while (now && ~t) {
			int mi = min(b[t].cnt, now);
			b[t].cnt -= mi;
			now -= mi;
			if (!b[t].cnt) t--;
		}
	}
	cout << ans << endl;


	return 0;
}
