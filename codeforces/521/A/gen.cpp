#include <bits/stdc++.h>

using namespace std;

int main() {
	srand(time(0));
	int a = rand() % 100, b = rand() % 100, c = rand() % 100, d = rand() % 100;
	if (a > b) swap(a, b);
	if (b > c) swap(b, c);
	if (c > d) swap(c, d);
	cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << endl;
	int sum = a + b + c + d;
	int ave = sum / 4;
	cout << ave << ' ' << ave << ' ' << ave << ' ' << sum - ave * 3 << endl;
	cout << (a + b + c) * ave + d * (sum - ave * 3) << endl;
	cout << a * a + b * b + c * c + d * d << endl;
	cout << d * sum << endl;


	return 0;
}
