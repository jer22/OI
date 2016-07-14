#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MOD = 999911659;

int n, G;
int divs[100005], num = 0;
void init() {
	for (int i = 1; i * i <= n; i++) {
		if (!(n % i)) {
			divs[num++] = i;
			if (i * i != n)
				divs[num++] = n / i;
		}
	}
	sort(divs, divs + num);
}

long long power(long long a,long long i,long long p) {
	if (i == 0) return 1 % p;
	long long ans = 1;
	long long base = a;
	while (i) {
		if (i & 1) (ans *= base) %= p;
		(base *= base) %= p;
		i >>= 1;
	}
	return ans;
}

long long Comb(long long a, long long b, long long p) {
	if (a < b) return 0;
	if (a == b) return 1;
	if (b > a - b) b = a - b;
	long long ans = 1, ca = 1, cb = 1;
	for (long long i = 0; i < b; ++i) {
		ca = (ca * (a - i)) % p;
		cb = (cb * (b - i)) % p;
	}
	ans = (ca * power(cb, p - 2, p)) % p;
	return ans;
}

long long Lucas(int n, int m, int p) {
	long long ans = 1;
	while(n != 0 && m != 0) {
		ans = (ans * Comb(n % p, m % p, p)) % p;
		n /= p;
		m /= p;
	}
	return ans;
}

long long exgcd(long long a, long long b, long long &x, long long &y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	long long ans = exgcd(b, a % b, x, y);
	long long temp = x;
	x = y;
	y = temp - a / b * y;
	return ans;
}

long long CRT(long long a[], long long m[], int cnt) {
	long long M = 1;
	for(int i = 0;i < cnt; i++) M *= m[i];
	long long ans = 0;
	for(int i = 0; i < cnt; i++) {
		long long x, y;
		long long tm = M / m[i];
		exgcd(tm, m[i], x, y);
		ans = (ans + tm * x * a[i]) % M;
	}
	return (ans + M) % M;
}

long long t[4] = {0, 0, 0, 0};
long long mods[4] = {2, 3, 4679, 35617};
int main() {
	freopen("1951.in", "r", stdin);
	cin >> n >> G;
	G %= MOD;
	if (!G) {
		cout << 0 << endl;
		return 0;
	}
	init();
	
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < 4; j++)
			(t[j] += Lucas(n, divs[i], mods[j])) %= mods[j];
	}
	long long ans = CRT(t, mods, 4);
	cout << power(G, ans, MOD) << endl;


	return 0;
}
