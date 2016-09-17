#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int T, n;
int main() {
	freopen("1005.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		if (n & 1) printf("Balanced\n");
		else printf("Bad\n");
	}



	return 0;
}
