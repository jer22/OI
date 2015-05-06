#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int T, n;
int brr[5] = {6, 2, 4, 8};

int s(int x) {
	if (x == 3) return 8;
	double y = x * log10(2);
	return (int)pow(10, y - (int)y);
}

int main() {
	freopen("g.in", "r", stdin);
	long long a = 1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%d %d\n", s(n), brr[n % 4]);
	}

	return 0;
}
