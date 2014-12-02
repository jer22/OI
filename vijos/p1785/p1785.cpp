#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
	freopen("p1785.in", "r", stdin);
	int n, k;
	scanf("%d %d", &n, &k);
	int ans = 0;
	while (k--) {
		int t = n / 2;
		ans += t;
		n -= t;
	}
	printf("%d\n", ans);
	return 0;
}
