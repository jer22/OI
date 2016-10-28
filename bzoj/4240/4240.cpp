#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

struct Node{
	int val, pos;
	Node() {}
	Node(int a, int b) : val(a), pos(b) {}
	bool operator < (const Node &n) const {
		if (val != n.val) return val < n.val;
		return pos < n.pos;
	}
};

int n;
Node arr[MAXN];
long long c[MAXN];
int lowbit(int x) {
	return x & (-x);
	}
void insert(int pos, int v) {
	for (int i = pos; i < MAXN; i += lowbit(i))
		c[i] += (long long)v;
}
long long getans(int pos) {
	long long ans = 0;
	for (int i = pos; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

int main() {
	freopen("4240.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].val);
		arr[i].pos = i;
		insert(i, 1);
	}
	sort(arr + 1, arr + n + 1);
	long long ans = 0;
	int r = 1;
	for (int i = 1; i <= n; i++) {
		if (r == i) {
			for (; r <= n; r++) {
				if (arr[r].val == arr[i].val)
					insert(arr[r].pos, -1);
				else break;
			}
		}
		ans += min(getans(arr[i].pos - 1), getans(n) - getans(arr[i].pos));
	}
	printf("%lld\n", ans);
	return 0;
}
