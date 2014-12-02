#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXM 82

using namespace std;

struct Num {
	int num[220];
	int len;
	void print() {
		for (int i = len - 1; i >= 0; i--) {
			printf("%d", num[i]);
		}
		printf("\n");
	}
	void init(int a) {
		memset(num, 0, sizeof(num));
		len = 1;
		num[0] = a;
	}
};

int n, m;
int arr[MAXM];
Num dp[MAXM][MAXM];
Num binary[MAXM];
Num re;

Num operator + (Num a, Num b) {
	Num c;
	memset(c.num, 0, sizeof(c.num));
	c.len = max(a.len, b.len);
	for (int i = 0; i < c.len; i++) {
		c.num[i] += a.num[i] + b.num[i];
		c.num[i + 1] += c.num[i] / 10;
		c.num[i] %= 10;
	}
	if (c.num[c.len]) c.len++;
	return c;
}

Num operator * (Num a, int b) {
	Num c;
	c.len = a.len;
	memset(c.num, 0, sizeof(c.num));
	for (int i = 0; i < a.len; i++) {
		c.num[i] += a.num[i] * b;
		c.num[i + 1] += c.num[i] / 10;
		c.num[i] %= 10;
	}
	c.len++;
	while (c.num[c.len - 1] >= 10) {
		c.num[c.len] += c.num[c.len - 1] / 10;
		c.num[c.len - 1] %= 10;
		c.len++;
	}
	while (c.len > 1 && !c.num[c.len - 1]) c.len--;
	return c;
}

Num BigIntegerMax(Num a, Num b) {
	if (a.len > b.len) return a;
	if (a.len < b.len) return b;
	for (int i = a.len - 1; i >= 0; i--) {
		if (a.num[i] > b.num[i]) {
			return a;
		}
		if (a.num[i] < b.num[i]) {
			return b;
		}
	}
	return a;
}

int main() {
	freopen("1005.in", "r", stdin);
	scanf("%d %d", &n, &m);
	re.init(0);
	binary[0].init(1);
	for (int i = 1; i <= m; i++) {
		binary[i] = binary[i - 1] * 2;
	}

	for (int i = 0; i < n; i++) {
		memset(arr, 0, sizeof(arr));
		memset(dp, 0, sizeof(dp));
		for (int j = 1;  j <= m; j++) {
			scanf("%d", &arr[j]);
		}
		// dp[j][k][l] : 已经取走了j个数，剩余第k ~ l个数
		// 取了j个数，还剩m - j == l - k + 1个数
		for (int j = 0; j < m; j++) {
			for (int k = 1; k <= j + 1; k++) {
				int l = k + m - j - 1;
				dp[j + 1][k + 1] = BigIntegerMax(dp[j][k] + binary[j + 1] * arr[k], dp[j + 1][k + 1]);
				dp[j + 1][k] = BigIntegerMax(dp[j][k] + binary[j + 1] * arr[l], dp[j + 1][k]);
			}
		}
		Num ans;
		ans.init(0);
		for (int j = 1; j <= m; j++) {
			ans = BigIntegerMax(ans, dp[m][j + 1]);
		}
		re = re + ans;
	}
	re.print();
	return 0;
}
