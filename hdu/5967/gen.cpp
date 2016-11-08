#include <bits/stdc++.h>

using namespace std;


int main() {
	freopen("5967.in", "w", stdout);
	srand(time(0));
	int n = 10, m = 100;
	cout << n << ' ' << m << endl;
	for (int i = 1; i <= n; i++) {
		int t = rand() % (n + 1);
		while (t == i) t = rand() % (n + 1);
		cout << t << " \n"[i == n];
	}
	for (int i = 1; i <= m; i++) {
		int op = rand() % 2 + 1;
		cout << op << ' ';
		if (op == 1) {
			int a = rand() % n + 1;
			int b = rand() % (n + 1);
			while (b == a) b = rand() % (n + 1);
			cout << a << ' ' << b << endl;
		} else {
			int a = rand() % n + 1;
			cout << a << endl;
		}
	}


	return 0;
}
