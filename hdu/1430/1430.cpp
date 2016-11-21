#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <map>

#define pli pair<long long, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

long long s = 0ll;
map<long long, bool> vis;
map<long long, pli > pre;

void print(long long x) {
	for (long long i = 7; i >= 0; i--)
		cout << ((x >> (i << 2ll)) & ((1ll << 4ll) - 1)) << " \n"[!i];
}

long long tr1(long long x) {
	long long y = 0ll;
	for (long long i = 0ll; i < 4ll; i++) {
		y |= (((x >> (i << 2ll)) & ((1ll << 4ll) - 1ll)) << ((7ll - i) << 2ll));
		y |= (((x >> ((7ll - i) << 2ll)) & ((1ll << 4ll) - 1ll)) << (i << 2ll));
	}
	return y;
}

long long tr2(long long x) {
	long long fir = x >> 16ll;
	long long sec = x & ((1ll << 16) - 1ll);

	fir = (((fir & 15ll) << 12ll) | ((fir >> 4ll) & 4095ll));
	sec = (((sec & 4095ll) << 4ll) | (sec >> 12ll));
	return ((fir << 16ll) | sec);
}

long long tr3(long long x) {
	long long a = ((x >> 24ll) & 15ll);
	long long b = ((x >> 20ll) & 15ll);
	long long c = ((x >> 8ll) & 15ll);
	long long d = ((x >> 4ll) & 15ll);
	long long y = x & ((15ll << 28ll) | (15ll << 16ll) | (15ll << 12ll) | 15ll);
	y |= ((a << 20ll) | (b << 8ll) | (c << 4ll) | (d << 24ll));
	return y;
}

void bfs() {
	queue<long long> q;
	q.push(s);
	while (!q.empty()) {
		long long cur = q.front();
		q.pop();
		long long nx = tr1(cur);
		if (vis.find(nx) == vis.end()) {
			vis[nx] = 1;
			pre[nx] = mp(cur, 1);
			q.push(nx);
		}
		nx = tr2(cur);
		if (vis.find(nx) == vis.end()) {
			vis[nx] = 1;
			pre[nx] = mp(cur, 2);
			q.push(nx);
		}
		nx = tr3(cur);
		if (vis.find(nx) == vis.end()) {
			vis[nx] = 1;
			pre[nx] = mp(cur, 3);
			q.push(nx);
		}
	}
}

int pos[9];
int main() {
	freopen("1430.in", "r", stdin);
	for (long long i = 1ll; i <= 8ll; i++) {
		s |= (i << ((8ll - i) << 2ll));
	}
	vis[s] = 1;
	bfs();
	char sta[9], des[9];
	while (~scanf("%s", sta)) {
		scanf("%s", des);
		for(int i = 0; i < 8; i++)
			pos[sta[i] - '0'] = i + 1;
		long long t = 0;
		for (int i = 0; i < 8; i++)
			t |= ((long long)(pos[des[i] - '0']) << ((7ll - i) << 2ll));
		stack<char> ans;
		while (t != s) {
			ans.push(pre[t].second + 'A' - 1);
			t = pre[t].first;
		}
		while (!ans.empty()) {
			printf("%c", ans.top());
			ans.pop();
		}
		printf("\n");

	}
	// print(tr3(s));

	return 0;
}
