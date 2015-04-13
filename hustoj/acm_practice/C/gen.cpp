#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

int len = 100;
int main() {
	freopen("c.in", "w", stdout);
	srand(time(0));
	cout << 1 << endl;
	int n = rand() % len + 1, m = rand() % len + 1;
	cout << n << ' ' << m << endl;
	int x = rand() % len + 1, y = rand() % len + 1;
	while (x > n) x = rand() % len + 1;
	while (y > m) y = rand() % len + 1;
	cout << x << ' ' << y << ' ';
	x = rand() % len + 1, y = rand() % len + 1;
	while (x > n) x = rand() % len + 1;
	while (y > m) y = rand() % len + 1;
	cout << x << ' ' << y << endl;

	return 0;
}
