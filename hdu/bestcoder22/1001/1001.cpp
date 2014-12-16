#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;

int T;
int n;
int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int res = 0;
		int base = 0;
		while ((long long)1 << base <= n) base++;
		base--;
		while (n) {
			res += (1 << base) * (n & 1);
			n >>= 1;
			base--;
		}
		printf("%d\n", res);
	}


	return 0;
}
