#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n;
int main() {
	freopen("1022.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int x = 0;
		int a;
		bool y = false;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a);
			x ^= a;
			if (a > 1) y = true;
		}
		if (x && y || !x && !y) printf("John\n");
		else printf("Brother\n");
	}
	return 0;
}
