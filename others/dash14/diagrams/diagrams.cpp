#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct Num {
	int arr[2000];
	int len;
	void print() {
		for (int i = len - 1; i >= 0; i--) {
			printf("%d", arr[i]);
		}
		printf("\n");
	}
};

int n;
Num dp[110][110];

Num operator + (Num a, Num b) {
	Num c;
	memset(c.arr, 0, sizeof(c.arr));
	c.len = max(a.len, b.len);
	for (int i = 0; i < c.len; i++) {
		c.arr[i] += a.arr[i] + b.arr[i];
		c.arr[i + 1] += c.arr[i] / 10;
		c.arr[i] %= 10;
	}
	if (c.arr[c.len]) c.len++;
	return c;
}

int main() {
	freopen("diagrams.in", "r", stdin);
	freopen("diagrams.out", "w", stdout);
	scanf("%d", &n);
	if (n == 1) {
		printf("1\n");
		return 0;
	}
	Num x;
	memset(x.arr, 0, sizeof(x.arr));
	x.arr[0] = 1;
	x.len = 1;
	dp[1][1] = x;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = 0; k <= min(j, i - 1); k++) {
				dp[i][j] = dp[i - 1][k] + dp[i][j];
			}
			dp[i][j] = dp[i][j] + x;
		}
	}
	Num ans;
	memset(ans.arr, 0, sizeof(ans.arr));
	ans.len = 0;
	for (int i = 1; i <= n; i++) {
		ans = dp[n][i] + ans;
	}
	ans.print();

	return 0;
}
