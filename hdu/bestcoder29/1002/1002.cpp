#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MOD 10000007

using namespace std;

struct Martrix{
	int n;
	int num[5][5];
	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << num[i][j] << ' ';
			}
			cout << endl;
		}
	}
};

int n, k;
Martrix origin;
Martrix base;

inline Martrix operator *(Martrix a, Martrix b) {
	Martrix c;
	c.n = 3;
	memset(c.num, 0, sizeof(c.num));
	int i, j, k;
	for (i = 0; i < a.n; i++) {
		for (j = 0; j < b.n; j++) {
			for (k = 0; k < a.n; k++) {
				int temp = a.num[i][k] * b.num[k][j];
				temp %= MOD;
				c.num[i][j] += temp;
				c.num[i][j] %= MOD;
			}
		}
	}
	return c;
}

void pow() {
	base.n = 3;
	memset(base.num, 0, sizeof(base.num));
	base.num[1][0] = base.num[0][1] = base.num[0][2] = 1;
	base.num[1][1] = base.num[1][2] = base.num[2][2] = 1;
	while (k) {
		if (k & 1) {
			origin = origin * base;
		}
		k >>= 1;
		base = base * base;
	}
}

int main() {
	freopen("1002.in", "r", stdin);
	
	while (~scanf("%d %d", &n, &k)) {
		int sum = 0;
		int first = 0, second = 0;
		int x;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			sum += x;
			sum %= 10000007;
			if (x > first) {
				second = first;
				first = x;
			} else if (x > second) second = x;
		}
		memset(origin.num, 0, sizeof(origin.num));
		origin.n = 3;
		origin.num[0][0] = second;
		origin.num[0][1] = first;
		origin.num[0][2] = sum;
		pow();
		cout << origin.num[0][2] << endl;
	}


	return 0;
}
