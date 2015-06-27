#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int main() {
	scanf("%d", &n);
	if (n % 2) {
		printf("black\n");
		return 0;
	}
	printf("white\n1 2\n");
	return 0;
}
