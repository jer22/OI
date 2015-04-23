#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n, m;
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		int a = 0, b = 0;
		int t;
		for (int i = 0; i < n; i++) {
			scanf("%d", &t);
			a += t;
		}
		for (int i = 0; i < m; i++) {
			scanf("%d", &t);
			b += t;
		}
		if (a > b) printf("Calem\n");
		else if (a < b) printf("Serena\n");
		else printf("Draw\n");
	}


	return 0;
}
