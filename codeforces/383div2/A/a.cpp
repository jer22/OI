#include <bits/stdc++.h>

using namespace std;

int power(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = res * a % 10;
		a = a * a % 10;
		b >>= 1;
	}
	return res;
}

int n;
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &n);
	cout << power(1378, n) << endl;

	return 0;
}
