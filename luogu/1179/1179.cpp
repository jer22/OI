#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int l, r;

int getSum(int i) {
	int ans = 0;
	while (i) {
		if (i % 10 == 2) ans++;
		i /= 10;
	}
	return ans;
}

int main() {
	freopen("1179.in", "r", stdin);
	scanf("%d %d", &l, &r);
	int ans = 0;
	for (int i = l; i <= r; i++) {
		ans += getSum(i);
	}
	printf("%d\n", ans);
	return 0;
}
