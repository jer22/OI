#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000005;

int n, q;
vector<pair<int, int> > c[MAXN];
int now = 0, mark = 0;

int lowbit(int x) {
	return x & (-x);
}

void add(int pos, int x) {
	for (int i = pos; i <= n; i += lowbit(i)) {
		int val = 0;
		if (!c[i].empty()) val = c[i].back().second;
		val += x;
		c[i].push_back(make_pair(now, val));
	}
}

int low(int pos, int tim) {
	if (c[pos].empty()) return 0;
	int l = 0, r = c[pos].size() - 1;
	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (c[pos][mid].first <= tim)
			l = mid;
		else r = mid - 1;
	}
	if (c[pos][l].first <= tim)
		return c[pos][l].second;
	else return 0;
}

int getsum(int pos, int tim) {
	int ans = 0;
	for (int i = pos; i > 0; i -= lowbit(i)) {
		ans += low(i, tim);
	}
	return ans;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &q);
	int op;
	int a, b, x, t;
	for (int i = 0; i < q; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d", &a, &x);
			a = a ^ mark;
			now++;
			add(a, x);
			mark = getsum(a, now) - getsum(a - 1, now);
		} else {
			scanf("%d %d %d", &a, &b, &t);
			a = a ^ mark;
			b = b ^ mark;
			int ans = getsum(b, t) - getsum(a - 1, t);
			mark = ans;
			printf("%d\n", ans);
		}
		// cout << mark << endl;
	}


	return 0;
}
