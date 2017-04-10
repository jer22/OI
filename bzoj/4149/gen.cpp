#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	freopen("4149.in", "w", stdout);
	int n = 200;
	srand(time(0));
	cout << n << endl;
	for (int i = 1; i <= n; i++) {
		int x = rand() % 200 - 100;
		cout << x << ' ';
	}

	return 0;
}
