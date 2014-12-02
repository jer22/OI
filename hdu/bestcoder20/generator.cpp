#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
	freopen("text", "w", stdout);
	printf("1\n100000\n");
	for (int i = 1; i <= 100000; i++) {
		int a = 1, b = 0;
		
		while (a > b) {
			a = rand() % 10000 + 1;
			b = rand() % 10000 + 1;
		}
		printf("%d %d\n", a, b);
	}
}
