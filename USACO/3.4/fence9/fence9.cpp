/*
ID:shijiey1
PROG:fence9
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m, p;

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int main() {
	freopen("fence9.in", "r", stdin);
	freopen("fence9.out", "w", stdout);
	scanf("%d %d %d", &n, &m, &p);
	int b = gcd(n, m) + gcd(abs(p - n), m) + p;
	int a = p * m / 2 + 1 - (b / 2);
	printf("%d\n", a);
	return 0;
}
