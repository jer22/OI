#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	long long l, r;
	Node() {}
	Node(long long a, long long b) : l(a), r(b) {}
	bool operator < (const Node &n) const {
		return r < n.r;
	}
};

int n;
Node arr[200005];
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	long long a, b;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &a, &b);
		arr[i] = Node(a - b, a + b);
	}
	sort(arr, arr + n);
	int ans = 0;
	long long pos = -10000000000000000;
	for (int i = 0; i < n; i++) {
		if (arr[i].l >= pos) {
			ans++;
			pos = arr[i].r;
		}
	}
	printf("%d\n", ans);

	return 0;
}
