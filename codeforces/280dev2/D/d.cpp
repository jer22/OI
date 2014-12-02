#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n, x, y;
int arr[2000005];
int l = 0;
int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int main() {
	// freopen("d.in", "r", stdin);
	scanf("%d %d %d", &n, &x, &y);
	int t = gcd(x, y);
	x /= t;
	y /= t;
	l = x + y;
	arr[l] = arr[l - 1] = 2;
	double xx = (double)1 / x;
	double yy = (double)1 / y;
	double a = xx;
	double b = yy;
	for (int i = 1; i <= l - 2; i++) {
		if (a < b) {
			arr[i] = 0;
			a += xx;
		} else {
			arr[i] = 1;
			b += yy;
		}
	}
	// for (int i = 1; i <= l; i++) {
	// 	printf("%d %d\n", i, arr[i]);
	// }
	for (int i = 0; i < n; i++) {
		scanf("%d\n", &t);
		t = (t - 1) % l + 1;
		if (arr[t] == 0) {
			printf("Vanya\n");
			continue;
		} else if (arr[t] == 1) {
			printf("Vova\n");
			continue;
		} else {
			printf("Both\n");
			continue;
		}
	}

	return 0;
}
