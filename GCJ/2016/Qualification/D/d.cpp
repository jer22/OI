#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
long long len, c, s;

long long power(long long a, long long b) {
	long long ans = 1;
	for (; b; a *= a, b >>= 1) if (b & 1) ans *= a;
	return ans;
}

long long p[105];
int main() {
	freopen("d.in", "r", stdin);
	freopen("o", "w", stdout);
	scanf("%d", &T);
	p[0] = 0;
	p[1] = 1;
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d:", cas);
		cin >> len >> c >> s;
		for (int i = 2; i <= c + 1; i++) p[i] = p[i - 1] * len;
		if (c == 1) {
			if (s != len) cout << " IMPOSSIBLE" << endl;
			else {
				cout << ' ';
				for (int i = 1; i <= len; i++) cout << i << " \n"[i == len];
			}
			continue;
		}
		if (len == 1) {
			cout << ' ' << 1 << endl;
			continue;
		}
		if (s * c < len) cout << " IMPOSSIBLE" << endl;
		else {
			int j = 0;
			for (int i = 1; i <= s; i++) {
				cout << ' ';
				if (j + c >= len) {
					long long pp = 0;
					for (int k = 1; k <= c; k++) {
						pp += p[c - k + 1] * j;
						if (j < len - 1) j++;
					}
					cout << pp + 1;

					break;
				} else {
					long long pp = 0;
					for (int k = 1; k <= c; k++) {
						pp += p[c - k + 1] * j;

						j++;
					}
					cout << pp + 1;
				}
			}
			cout << endl;
		}
	}

	return 0;
}
