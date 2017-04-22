#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;

int mob[MAXN], p[2000], check[MAXN], tot;
void getMob() {
	mob[1] = 1;
	for (int i = 2; i <= 2000; i++) {
		if (!check[i]) {
			p[++tot] = i;
			mob[i] = -1;
		}
		for (int j = 1; j <= tot; j++) {
			if (i * p[j] > 2000) break;
			check[i * p[j]] = 1;
			if (i % p[j] == 0) {
				mob[i * p[j]] = 0;
				break;
			}
			else mob[i * p[j]] = -mob[i];
		}
	}
}

int a, b, c;
int g(int d, int i) {
	int ans = 0;
	for (int j = 1; j <= d; ++j)
		if (__gcd(j, i) == 1) ans += d / j;
	return ans;
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d %d %d", &a, &b, &c);
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
	getMob();
	int ans = 0;
	for (int i = 1; i <= a; ++i) {
		for (int j = 1; j <= b; ++j) {
			if (__gcd(i, j) != 1) continue;
			ans += mob[j] * (a / i) * g(b / j, i) * g(c / j, i);
		}
	}
	cout << (ans & ((1 << 30) - 1)) << endl;


	return 0;
}
