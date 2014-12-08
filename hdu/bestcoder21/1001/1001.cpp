#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int main() {
	freopen("1001.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (n - 15 > 0) {
			printf("%d %d %d %d %d\n", n - 15, n - 7, n - 4, n - 2, n - 1);
		} else if (n - 7 > 0) {
			printf("%d %d %d %d\n", n - 7, n - 4, n - 2, n - 1);
		}
		else if (n - 4 > 0) {
			printf("%d %d %d\n", n - 4, n - 2, n - 1);
		}
		else if (n - 2 > 0) {
			printf("%d %d\n", n - 2, n - 1);
		}
		else if (n - 1 > 0) {
			printf("%d\n", n - 1);
		}
	}
	return 0;
}
