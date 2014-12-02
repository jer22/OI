#include <iostream>
#include <cstdio>
#include <cstring>

#define MOD 100003

using namespace std;

inline long long pow(long long a, long long b) {
	long long re = 1;
	while (b) {
		if (b & 1) {
			re = (re * a) % MOD;
		}
		a = (a * a) % MOD;
		b >>= 1LL;
	}
	return re;
}

int main( void ) {
	long long a, b;
	cin >> a >> b;
	long long r = pow(a, b);
	long long m = (pow(a - 1, b - 1) * (a % MOD)) % MOD;
	r += MOD;
	cout << (r - m) % MOD << endl;
	return 0;
}
