#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int n;
int isprime[1000000];
int pp[400000];
int primeNum = 0;

void initPrime() {
	isprime[1] = 1;
	for (int i = 2; i < 1000000; i++) {
		if (!isprime[i]) {
			for (int j = i << 1; j < 1000000; j += i) {
				isprime[j] = 1;
			}
		}
	}
}

bool prime(int n) {
	if (n == 1) return false;
	for (int i = 2; i <= sqrt(n); i++) {
		if (!(n % i)) {
			return false;
		}
	}
	return true;
}

int main() {
	freopen("1001.in", "r", stdin);
	initPrime();
	// for (int i = 2; i < 1000000; i++) {
	// 	if (!isprime[i]) {
	// 		pp[primeNum++] = i;
	// 	}
	// }

	while (scanf("%d", &n) != EOF) {
		int t = n;
		int i;
		int ans = -1;
		for (i = 2; i <= sqrt(n); i++) {
			while (!(n % i)) {
				n /= i;
				if (!isprime[i]) {
					ans = i;
				}
			}
		}
		ans = max(ans, n);
		if (ans == 1) {
			printf("0\n");
			continue;
		}
		printf("%d\n", t / ans);
	}

	return 0;
}
