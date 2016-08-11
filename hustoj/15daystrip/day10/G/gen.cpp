#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;


int main() {
	freopen("g.in", "w", stdout);
	srand(time(0));
	int t = 5;
	cout << t << endl;
	for (int j = 0; j < t; j++) {
		cout << 100000 << endl;
		for (int i = 1; i <= 100000; i++)
			cout << rand() % 200000 - 100000 << ' ' << rand() % 200000 - 100000 << endl;
	}

	return 0;
}
