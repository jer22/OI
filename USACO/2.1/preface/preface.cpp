/*
ID:shijiey1
PROG:preface
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int map[5] = {0, 1, 2, 3, 1};
int i, v, x, l, c, d, m;
int main() {
	freopen("preface.in", "r", stdin);
	freopen("preface.out", "w", stdout);
	scanf("%d", &n);
	for (int ii = 1; ii <= n; ii++) {
		int a = ii % 10;
		i += map[a % 5];
		if (a >= 4 && a <= 8) v++;
		else if (a == 9) x++;
		a = ii / 10 % 10;
		x += map[a % 5];
		if (a >= 4 && a <= 8) l++;
		else if (a == 9) c++;
		a = ii / 100 % 10;
		c += map[a % 5];
		if (a >= 4 && a <= 8) d++;
		else if (a == 9) m++;
		a = ii / 1000 % 10;
		m += map[a % 5];
	}
	if (i) printf("I %d\n", i);
	if (v) printf("V %d\n", v);
	if (x) printf("X %d\n", x);
	if (l) printf("L %d\n", l);
	if (c) printf("C %d\n", c);
	if (d) printf("D %d\n", d);
	if (m) printf("M %d\n", m);

	return 0;
}
