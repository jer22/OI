#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 100010
#define MOD 99999997

using namespace std;

struct Node {
	int val;
	int pos;
	bool operator < (const Node &n) const {
		return val < n.val;
	}
};

int n;
Node a[MAXN];
Node b[MAXN];
Node arr[MAXN];
int reflect[MAXN];
int c[MAXN];

int lowBit(int x) {
	return x & (-x);
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
		ans %= MOD;
		x -= lowBit(x);
	}
	return ans;
}

int main() {
	freopen("1966.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].val);
		a[i].pos = i;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i].val);
		b[i].pos = i;
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) {
		arr[a[i].pos].val = b[i].pos;
		arr[a[i].pos].pos = a[i].pos;
	}
	memset(c, 0, sizeof(c));
	sort(arr + 1, arr + n + 1);
	for (int i = 1; i <= n; i++) {
		reflect[arr[i].pos] = i;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		update(reflect[i]);
		ans += i - getSum(reflect[i]);
		ans %= MOD;
	}
	printf("%d\n", ans);
	return 0;
}
