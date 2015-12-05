#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int T;
long long n;
long long t[60];

void init() {
	t[1] = 1;
	int id = 1;
	long long j = 2;
	while (j < 10000000000000000ll) {
		j <<= 1;
		id++;
		t[id] = (t[id - 1] << 1) + (j >> 1);
	}
}

int get(long long x) {
	int id = 1;
	long long j = 2;
	while (j - 1 <= x) {
		j <<= 1;
		id++;
	}
	return id - 1;
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	init();
	while (T--) {
		cin >> n;
		// if (n == 1) {
		// 	printf("1\n");
		// 	return 0;
		// } else if (n == 2) {
		// 	printf("2\n");
		// 	return 0;
		// } else if (n == 3) {
		// 	printf("4\n");
		// 	return 0;
		// }
		long long ans = 0;
		int tmp = get(n);
		ans += t[tmp];
		n -= (1ll << tmp) - 1;
		ans += n;
		while (n) {
			n--;
			tmp = get(n);
			ans += t[tmp];
			n -= (1ll << tmp) - 1;
			ans += n;
		}
		cout << ans << endl;
	}


	return 0;
}
