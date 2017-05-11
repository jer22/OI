#include <bits/stdc++.h>

#define lowbit(x) ((x) & (-(x)))

using namespace std;
const long long INF = 100000000000000000ll;

long long num[1000005];
long long cost[1000005];
void insert(int p, long long v, long long *c) {
	for (int i = p; i <= 1000000; i += lowbit(i))
		c[i] += v;
}
long long getsum(int p, long long *c) {
	long long ans = 0;
	for (int i = p; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

int main() {
	freopen("input.txt", "r", stdin);
	char op[10];
	long long n, c, m;
	long long tot = 0;
	map<int, long long> pri;
	while (~scanf("%s", op)) {
		if (op[0] == 'A') {
			scanf("%lld %lld", &n, &c);
			insert(c, n, num);
			insert(c, c * n, cost);
			tot += n;
			pri[c] += n;
		} else {
			scanf("%lld %lld", &n, &m);
			int l = 1, r = 1000000;
			long long nn = 0;
			if (tot < n) {
				printf("UNHAPPY\n");
				continue;
			}
			while (l < r) {
				int mid = (l + r >> 1) + 1;
				long long ss = getsum(mid, num);
				if (ss <= n) {
					l = mid;
					nn = ss;
				} else r = mid - 1;
			}
			long long totcost = getsum(l, cost);
			map<int, long long>::iterator ett = pri.upper_bound(l);
			if (ett != pri.end()) totcost += (long long)(ett -> first) * (n - nn);
			if (totcost <= m) {
				printf("HAPPY\n");
				tot -= n;
				for (map<int, long long>::iterator it = pri.begin(); it != pri.end();) {
					if (it -> first <= l) {
						insert(it -> first, -(it -> second), num);
						insert(it -> first, -((it -> second) * (it -> first)), cost);
						it = pri.erase(it);
					}
					else break;
				}
				map<int, long long>::iterator it = pri.upper_bound(l);
				if (it != pri.end()) {
					assert(it -> second > n - nn);
					insert(it -> first, -(n - nn), num);
					insert(it -> first, -((n - nn) * (it -> first)), cost);
					pri[it -> first] -= n - nn;
				}
			} else printf("UNHAPPY\n");
		}
	}


	return 0;
}
