#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

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
	srand(time(0));
	freopen("input.txt", "w", stdout);
	n = 1000000, q = 100000;
	printf("%d %d\n", n, q);
	int a, b, x, t;
	for (int i = 0; i < q; i++) {
		double op = (double)rand() / RAND_MAX;
		if (op < 0.7) {
			a = rand() % n + 1;
			x = rand() % 1000 + 1;
			now++;
			add(a, x);
			printf("1 %d %d\n", a^mark, x);
			mark = getsum(a, now) - getsum(a - 1, now);
		} else {
			a = rand() % n + 1;
			b = rand() % n + 1;
			if (a > b) swap(a, b);
			t = rand() % (now + 1);
			int ans = getsum(b, t) - getsum(a - 1, t);
			a = a ^ mark;
			b = b ^ mark;
			printf("2 %d %d %d\n", a, b, t);
			mark = ans;
		}
		// cout << mark << endl;
	}


	return 0;
}
