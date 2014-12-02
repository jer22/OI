#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 40010

using namespace std;

struct Node {
	int val;
	int pos;	// pos:第几个读入的数字
	bool operator < (const Node &n) const {
		return val < n.val;
	}
};

int n;
Node node[MAXN];
int c[MAXN];
int reflect[MAXN];	// reflect[i]:第i个读入的数字的下标

int lowBit(int i) {
	return i & (-i);
}

void update(int x) {
	while (x <= n) {
		c[x]++;
		x += lowBit(x);
	}
}

int getSum(int x) {
	int ans = 0;
	while (x > 0) {
		ans += c[x];
		x -=lowBit(x);
	}
	return ans;
}

int main() {
	freopen("1908.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &node[i].val);
		node[i].pos = i;
	}
	sort(node + 1, node + n + 1);
	for (int i = 1; i <= n; i++) {
		reflect[node[i].pos] = i;
	}
	memset(c, 0, sizeof(c));
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		update(reflect[i]);
		ans += i - getSum(reflect[i]);
	}
	printf("%d\n", ans);
	return 0;
}
