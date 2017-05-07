#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("filth.in", "w", stdout);

	cout << 10000 << endl;
	for (int i = 1; i <= 5000; i++) {
		cout << i << endl;
	}
	srand(time(0));
	for (int i = 5011; i <= 10000; i++) {
		int n = rand() % 1000000 + 1;
		cout << n << endl;
	}
	for (int i = 1; i <= 10; i++)
		cout << 1000000 << endl;


	return 0;
}
