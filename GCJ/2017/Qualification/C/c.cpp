#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cassert>

#define unsigned unsigned long long

using namespace std;

unsigned n, k;

int main() {
	// freopen("c.in", "r", stdin);
	// freopen("out", "w", stdout);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d: ", cas);
		cin >> n >> k;
		if (k == 1) {
			cout << n / 2 << ' ' << (n - 1) / 2 << endl;
			continue;
		}
		unsigned x = n / 2, y = (n - 1) / 2;
		unsigned c1 = 1, c2 = 1;
		k--;
		unsigned p = 1;
		for (; k > (1ull << p); k -= (1ull << p), ++p) {
			if (x == y) {
				unsigned a = x / 2;
				unsigned b = (x - 1) / 2;
				x = a, y = b;
				c1 <<= 1, c2 <<= 1;
			} else {
				unsigned a = x / 2;
				unsigned b = (x - 1) / 2;
				unsigned c = y / 2;
				unsigned d = (y - 1) / 2;

				unsigned cc1 = 0, cc2 = 0;
				if (a == b) {
					x = a;
					cc1 = c1 << 1;
					if (c == d) {
						assert(a == c);
						y = a;
						cc2 = c2 << 1;
					} else {
						assert(c == d + 1);
						y = d;
						cc1 += c2;
						cc2 = c2;
					}
				} else {
					assert(a == b + 1);
					x = a, y = b;
					cc1 = cc2 = c1;
					if (c == d) {
						assert(b == c);
						cc2 += (c2 << 1);
					} else {
						assert(0);
					}
				}

				c1 = cc1, c2 = cc2;
			}

		}
		if (k <= c1) cout << x / 2 << ' ' << (x - 1) / 2 << endl;
		else cout << y / 2 << ' ' << (y - 1) / 2 << endl;

	}


	return 0;
}
