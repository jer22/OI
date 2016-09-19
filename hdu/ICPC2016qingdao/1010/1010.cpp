#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
long long m;

struct Node{
	long long wei, val;
	double key;
	Node() {}
	bool operator < (const Node &n) const {
		return key > n.key;
	}
};

Node arr[105];
long long sum[105];
long long best = 0;
int cnt = 0;

void dfs(int pos, long long nowwei, long long val) {
	cnt++;
	best = max(best, val);
	if (cnt > 2000000) return;
	if (pos == n) return;
	if (val + sum[n] - sum[pos] < best) return;
	for (int i = pos + 1; i <= n; i++) {
		if (nowwei + arr[i].wei <= m) dfs(i, nowwei + arr[i].wei, val + arr[i].val);
		if (cnt > 2000000) return;
	}
}

int main() {
	freopen("1010.in", "r", stdin);
	while (~scanf("%d %lld", &n, &m)) {
		for (int i = 1; i <= n; i++) {
			scanf("%lld %lld", &arr[i].wei, &arr[i].val);
			arr[i].key = double(arr[i].val) / double(arr[i].wei);
		}
		sort(arr + 1, arr + n + 1);
		for (int i = 1; i <= n; i++)
			sum[i] = sum[i - 1] + arr[i].val;
		best = 0;
		cnt = 0;
		dfs(0, 0, 0);
		printf("%lld\n", best);
	}



	return 0;
}
