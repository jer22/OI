#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

bool nice(int n) {
	if (n < 0) n = -n;
	while (n) {
		if ((n % 10) == 8) return true;
		n /= 10;
	}
	return false;
}

int n;
int main() {
	cin >> n;
	for (int i = 1; ; i++) {
		if (nice(n + i)) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}
