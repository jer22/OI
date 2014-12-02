#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
	freopen("magic.in", "w", stdout);
	int n;
	int a = 1000, b = 1000000;
	printf("%d %d\n", a, b);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			if (j) printf(" ");
			n = rand() % 2;
			printf("%d", n);
		}
		printf("\n");
	}
	int c, x, y;
	for (int i = 0; i < b; i++) {
		c = rand() % 2;
		x = rand() % a + 1;
		y = rand() % a+ 1;
		if (c) {
			printf("Q ");
		} else printf("T ");
		printf("%d %d\n", x, y);
	}
	return 0;
}
