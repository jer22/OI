#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define MOD 100000

using namespace std;

struct BigInteger {
	int a[2048];
	int len;
	void print() {
		printf("%d", a[len]);
		for (int i = len - 1; i > 0; i--) {
			for(int j = MOD / 10; j > a[i] && j >= 10; j /= 10)
				printf("0");
			printf("%d", a[i]);
		}
		printf("\n");
	}

	void operator *= (int b) {
		int t = 0;
		for (int i = 1; i <= len; i++) {
			a[i] = a[i] * b + t;
			t = a[i] / MOD;
			a[i] %= MOD;
		}
		if (t) a[++len] = t;
	}

	void operator /= (int b) {
		int now = 0;
		int t;
		for (int i = len; i > 0; i--) {
			t = a[i],
			a[i] = (now * MOD + t) / b,
			now = (now * MOD + t) % b;
		}
		for (; len > 1 && !a[len]; len--);
	}
} ans;



int n;
int sum;
int m;
int degree[1024];

int main( void ) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &degree[i]);
		degree[i] == -1 ? m++ : sum += degree[i] - 1;
	}
	if (n - 2 < sum) {
		printf("0\n");
		return 0;
	}
	ans.len = 1;
	ans.a[1] = 1;
	for (int i = 1; i <= n - 2 - sum; i++) {
		ans *= m;
	}
	for (int i = n - 2; i > sum; i--) {
		ans *= i,
		ans /= (n - i - 1);
	}
	for (int i = 1; i <= sum; i++) {
		ans *= i;
	}
	for (int i = 1; i <= n; i++) {
		if (degree[i] != -1) {
			for (int j = 1; j <= degree[i] - 1; j++) {
				ans /= j;
			}
		}
	}
	ans.print();
	return 0;
}
