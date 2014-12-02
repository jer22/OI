#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct Num {
	int s[150];
	int len;
	void print() {
		for (int i = len - 1; i >= 0; i--) {
			printf("%d", s[i]);
		}
		printf("\n");
	}
	void init(int a) {
		s[0] = a;
		len = 1;
	}
};

Num operator * (Num a, int b) {
	Num c;
	c.len = a.len;
	memset(c.s, 0, sizeof(c.s));
	for (int i = 0; i < a.len; i++) {
		c.s[i] += a.s[i] * b;
		c.s[i + 1] += c.s[i] / 10;
		c.s[i] %= 10;
	}
	c.len++;
	while (c.s[c.len - 1] >= 10) {
		c.s[c.len] += c.s[c.len - 1] / 10;
		c.s[c.len - 1] %= 10;
		c.len++;
	}

	while (c.len > 1 && !c.s[c.len - 1]) c.len--;
	return c;
}

Num operator + (Num a, Num b) {
	Num c;
	memset(c.s, 0, sizeof(c.s));
	c.len = max(a.len, b.len);
	for (int i = 0; i < c.len; i++) {
		c.s[i] += a.s[i] + b.s[i];
		c.s[i + 1] += c.s[i] / 10;
		c.s[i] %= 10;
	}
	if (c.s[c.len]) c.len++;
	return c;
}

int n, m;
Num arr[110][110];
int main() {
	//freopen("1655.in", "r", stdin);
	while (cin >> n >> m) {
		if (n < m) {
			printf("0\n");
			continue;
		}
		memset(arr, 0, sizeof(arr));
		for (int i = 0; i <= n; i++) {
			arr[i][1].init(1);
			arr[i][i].init(1);
		}
		for (int i = 3; i <= n; i++) {
			for (int j = 2; j <= m; j++) {
				arr[i][j] = (arr[i - 1][j] * j) + arr[i - 1][j - 1];
			}
		}
		arr[n][m].print();
	}

	return 0;
}
