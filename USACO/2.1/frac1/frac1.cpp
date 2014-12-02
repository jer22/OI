/*
ID:shijiey1
PROG:frac1
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node {
	int a, b;
	bool operator < (const Node &n) const {
		double c = (double)a / (double)b;
		double d = (double)n.a / (double)n.b;
		return c < d;
	}
}arr[20000];
int cnt = 0;
int n;

int gcd(int a, int b) {
	if (a < b) swap(a, b);
	if (!b && a == 1) return 1;
	if (!a || !b) return 0;
	if (!(a % b)) return b;
	return gcd(b, a % b);
}

int main() {
	freopen("frac1.in", "r", stdin);
	freopen("frac1.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			if (gcd(i, j) == 1) {
				Node t;
				t.a = j;
				t.b = i;
				arr[cnt++] = t;
			}
		}
	}
	sort(arr, arr + cnt);
	for (int i = 0; i < cnt; i++) {
		printf("%d/%d\n", arr[i].a, arr[i].b);
	}
	printf("1/1\n");
	return 0;
}
