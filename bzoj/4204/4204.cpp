#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int n, K;
struct Martrix{
	double arr[MAXN];
	void print() {
		for (int i = 1; i <= n; i++)
			printf("%.3lf\n", arr[i]);
	}
}base, ans;

Martrix operator * (Martrix a, Martrix b) {
	Martrix c;
	memset(c.arr, 0, sizeof(c.arr));
	for (int i = 1; i <= n; i++) {
		c.arr[i] = 0.;
		for (int j = 1; j <= n; j++)
			c.arr[i] += a.arr[j] * b.arr[(i - j + n) % n + 1];
	}
	return c;
}
Martrix operator ^(Martrix a, int b) {
	Martrix c;
	memset(c.arr, 0, sizeof(c.arr));
	c.arr[1] = 1;
	while (b) {
		if (b & 1) c = c * a;
		a = a * a;
		b >>= 1;
	}
	return c;
}

double m;
int main() {
	freopen("4204.in", "r", stdin);
	scanf("%d %lf %d", &n, &m, &K);
	base.arr[1] = (m - 1.) / m;
	base.arr[2] = 1. / m;
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &ans.arr[i]);
	}
	base = base ^ K;
	ans = base * ans;
	ans.print();


	return 0;
}
