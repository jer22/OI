#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int main() {
	freopen("4349.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int ans = 1;
		while (n) {
			if (n & 1) ans *= 2;
			n >>= 1;
		}
		cout << ans << endl;

	}

	return 0;
}
