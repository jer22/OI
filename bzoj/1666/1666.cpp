#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int n;
int main() {
	freopen("1666.in", "r", stdin);
	int ans = 0;
	scanf("%d", &n);
	while (n != 1) {
		if (n % 2) n = n * 3 + 1;
		else n >>= 1;
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}
