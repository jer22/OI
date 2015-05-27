#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	int val, pos;
	Node() {}
	Node(int a, int b) : val(a), pos(b) {}
	bool operator < (const Node &n) const {
		return val < n.val;
	}
};

int n, k;
Node arr[100005];
long long sum[100005];
int c[100005];

int lowbit(int x) {
	return x & -x;
}

void update(int x, int d) {
	for (int t = x; t <= 100000; t += lowbit(t)) {
		c[t] += d;
	}
}

int getsum(int x) {
	int ans = 0;
	for (int t = x; t; t -= lowbit(t)) {
		ans += c[t];
	}
	return ans;
}

int refl[100005];
int main() {
	freopen("c.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].val);
		arr[i].pos = i;
	}
	stable_sort(arr + 1, arr + n + 1);
	for (int i = 1; i <= n; i++)
		refl[arr[i].pos] = i;
	for (int i = 1; i <= n; i++) {
		sum[i] = getsum(n) - getsum(refl[i]);
		update(refl[i], 1);
		if (i - k > 0) {
			update(refl[i - k], -1);
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << sum[i] << " \n"[i == n];
	}
	return 0;
}
