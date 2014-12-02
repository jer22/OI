#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

long long GCD(long long a, long long b) {
	long long t;
	if (!a || !b)
		return 0;
	if (a < b) {
		t = a;
		a = b;
		b = t;
	}
	if (!(a % b)) {
		return b;
	} else {
		return GCD(b, a % b);
	}
}

long long LCM(long long a, long long b) {
	return a * b / GCD(a, b);
}

int n;
int a0, a1, b0, b1;
int main() {
    freopen("1072.in", "r", stdin);
	scanf("%d", &n);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt = 0;
		scanf("%d %d %d %d", &a0, &a1, &b0, &b1);
		for (int j = 1; j <= 10000; j++) {
			if (GCD(j, a0) == a1 && LCM(j, b0) == b1) {
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
