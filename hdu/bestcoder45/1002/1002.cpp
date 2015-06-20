#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 1005

using namespace std;

struct Node {
	int val;
	int pos;
	bool operator < (const Node &n) const {
		return val < n.val;
	}
};

int n, q;
int arr[MAXN];
Node temp[MAXN];
int c[MAXN];
int reflect[MAXN];

int lowBit(int i) {
	return i & (-i);
}

void update(int x, int d) {
	while (x <= n) {
		c[x] += d;
		x += lowBit(x);
	}
}

int getSum(int x) {
	int ans = 0;
	while (x > 0) {
		ans += c[x];
		x -= lowBit(x);
	}
	return ans;
}

int ans[1005][1005];
int main() {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);

	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			temp[j - i + 1].val = arr[j];
			temp[j - i + 1].pos = j - i + 1;
		}
		stable_sort(temp + 1, temp + n - i + 2);
		for (int j = 1; j <= n - i + 1; j++) {
			reflect[temp[j].pos] = j;
		}
		memset(c, 0, sizeof(c));
		for (int j = 1; j <= n - i + 1; j++) {  
			update(reflect[j], 1);  
			ans[i][j + i - 1] = ans[i][j + i - 2] + j - getSum(reflect[j]);  
		}  
	}
	int a, b;
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", ans[a][b]);
	}
	return 0;
}
