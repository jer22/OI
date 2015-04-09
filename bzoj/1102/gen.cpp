#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int main() {
	srand(time(0));
	freopen("1102.in", "w", stdout);
	int n = 1000;
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << rand() % 1000000000 << ' ';
		}
		cout << endl;
	}



	return 0;
}
