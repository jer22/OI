#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
	srand(time(0));
	freopen("1008.in", "w", stdout);
	cout << 1 << endl;
	int n = 100000;
	cout << n << ' ' << n << endl;
	for (int i = 1; i <= n; i++)
		cout << rand() % n + 1 << ' ';
	for (int i = 0; i < n; i++) {
		int t = rand() % 3 + 1;
		// if (t == 1) t = 
		cout << t << ' ';
		int a = rand() % n + 1;
		int b = rand() % n + 1;
		if (a > b) swap(a, b);
		cout << a << ' ' << b << ' ';
		if (t == 1) {
			
			int c = rand() % n + 1;
			cout  << c;
		}
		cout << endl;
	}


	return 0;
}
