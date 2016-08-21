#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long k;
int main() {
	freopen("c.in", "r", stdin);
	cin >> k;
	if ((k == 1) || (k == 2)) cout << "-1" << endl;
	else {
		if (k & 1) {
			long long i = k - 1 >> 1;
			long long a = i * i * 2 + i * 2;
			long long b = i * i * 2 + i * 2 + 1;
			cout << a << ' ' << b << endl;
		} else {
			long long i = k >> 1;
			long long a = i * i - 1;
			long long b = i * i + 1;
			cout << a << ' ' << b << endl;
		}
	}


	return 0;
}
