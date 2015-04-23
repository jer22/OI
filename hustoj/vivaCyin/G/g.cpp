#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n;
int a, b, c;
char f[5], g[5];
int prio[256];

int cal(int a, int b, char c) {
	if (c == '+') return a + b;
	if (c == '-') return a - b;
	if (c == '*') return a * b;
	if (c == '/') return a / b;
	if (c == '%') return a % b;
}

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d", &n);
	prio['+'] = prio['-'] = 1;
	prio['*'] = prio['/'] = prio['%'] = 2;
	while (n--) {
		scanf("%d %s %d %s %d", &a, f, &b, g, &c);
		char aa = f[0];
		char bb = g[0];
		int ans;
		if (prio[aa] >= prio[bb]) {
			ans = cal(a, b, aa);
			ans = cal(ans, c, bb);
		} else {
			ans = cal(b, c, bb);
			ans = cal(a, ans, aa);
		}
		printf("%d\n", ans);
	}


	return 0;
}
