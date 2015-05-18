#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <bitset>

using namespace std;

int n;
bitset<2000005> a;
int main() {
	freopen("3687.in", "r", stdin);
	scanf("%d", &n);
	int x;
	a[0] = 1;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		sum += x;
		a ^= (a << x);
	}
	int ans = 0;
	for (int i = 1; i <= sum; i++)
		if (a[i]) ans ^= i;
	printf("%d\n", ans);
	return 0;
}
