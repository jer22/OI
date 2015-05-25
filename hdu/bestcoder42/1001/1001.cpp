#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;

int main() {
	freopen("1001.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int ans = n * 2;
		int x;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				ans += x;
			}
		}
		printf("%d\n", ans);
	}


	return 0;
}
