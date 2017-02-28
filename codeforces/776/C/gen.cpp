#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("c.in", "w", stdout);
	cout << "100000 2\n";
	srand(time(0));
	for (int i = 0; i < 100000; i++)
		cout << (rand() % 2 * 2 - 1) * rand() % 1000000001 << ' ';

	return 0;
}
