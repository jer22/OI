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
	if (n < 1000000) return !isprime[n];
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
	for (int i = 2; i < 1000000; i++) {
		if (!isprime[i]) {
			pp[primeNum++] = i;
		}
	}

	while (scanf("%d", &n) != EOF) {
		if (prime(n)) {
			printf("1\n");
			continue;
		}
		int i;
		int ans = 0;
		for (i = 0; i < primeNum; i++) {
			if (!(n % pp[i])) {
				ans = pp[i];
			}
		}
		if ((!ans) || ans > n) printf("0\n");
		else printf("%d\n", n / ans);
	}

	return 0;
}
