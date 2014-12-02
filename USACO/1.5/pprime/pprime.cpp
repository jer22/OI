/*
ID:shijiey1
PROG:pprime
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int a, b;
int n = 0;
int arr[10000];

void isPrime(int t) {
	if (t >= a && t <= b) {
		bool flag = false;
		for (int i = 2; i <= sqrt(t); i++) {
			if (!(t % i)) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			arr[n++] = t;
		}
	}
}

int main() {
	freopen("pprime.in", "r", stdin);
	freopen("pprime.out", "w", stdout);
	scanf("%d %d", &a, &b);
	int t;
	if (a <= 2) arr[n++] = 2;
	for (int i = 1; i <= 9; i += 2) {
		isPrime(i);
		isPrime(i * 11);
		for (int j = 0; j <= 9; j++) {
			t = i * 101 + j * 10;
			isPrime(t);
			t = i * 1001 + j * 110;
			isPrime(t);
			for (int k = 0; k <= 9; k++) {
				t = i * 10001 + j * 1010 + k * 100;
				isPrime(t);
				t = i * 100001 + j * 10010 + k * 1100;
				isPrime(t);
				for (int l = 0; l <= 9; l++) {
					t = i * 1000001 + j * 100010 + k * 10100 + l * 1000;
					isPrime(t);
					t = i * 10000001 + j * 1000010 + k * 100100 + l * 11000;
					isPrime(t);
				}
			}
		}
	}
	sort(arr, arr + n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}
