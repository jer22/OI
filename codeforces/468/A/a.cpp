#include <bits/stdc++.h>

using namespace std;

int n;

void solve(int x) {
	if (x == 4) {
		printf("1 * 2 = 2\n");
		printf("2 * 3 = 6\n");
		printf("6 * 4 = 24\n");
	} else if (x == 5) {
		printf("2 - 1 = 1\n");
		printf("3 + 1 = 4\n");
		printf("4 * 5 = 20\n");
		printf("20 + 4 = 24\n");
	} else {
		printf("%d - %d = 1\n", x, x - 1);
		printf("1 * 1 = 1\n");
		solve(x - 2);
	}
}

int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	if (n < 4) cout << "NO" << endl;
	else {
		cout << "YES" << endl;
		solve(n);
	}
	return 0;
}
