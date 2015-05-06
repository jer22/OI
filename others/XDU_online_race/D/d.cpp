#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int a, b, p;
int main() {
	freopen("d.in", "r", stdin);
	while (~scanf("%d %d %d", &a, &b, &p)) {
		int ans = 1;
		for (int i = 1; i <= b; i++) {
			ans *= a;
			ans %= p;
		}
		printf("%d\n", ans);
	}


	return 0;
}
