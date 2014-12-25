#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main() {
	freopen("3766.in", "r", stdin);
	// freopen("3766.out", "w", stdout);
	char str[20];
	while (~scanf("%s", str)) {
		if (str[0] == 'E') break;
		int x = 0, y;
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] == '-' && !i) continue;
			else x = x * 10 + str[i] - '0';
		}
		cin >> y;
		y = abs(y);
		if (y < x) swap(x, y);
		if (y <= x << 1) {
			if (x == 1 && y == 1) printf("2\n");
			else if (x == 2 && y == 2) printf("4\n");
			else printf("%d\n", (x + y) / 3 + (x + y) % 3);
		} else {
			int ans = x;
			int c = (y - 2 * x) % 4;
			ans += c;
			ans += (y - 2 * x - c) / 2;
			if (y == 1 && x == 0) ans = 3;
			cout << ans << endl;
		}
	}
	return 0;
}
