#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool can(int n) {
	n -= 1;
	if (n % 5) return false;
	n /= 5;
	n *= 4;	// 1
	n -= 1;
	if (n % 5) return false;
	n /= 5;
	n *= 4; // 2
	n -= 1;
	if (n % 5) return false;
	n /= 5;
	n *= 4; // 3
	n -= 1;
	if (n % 5) return false;
	n /= 5;
	n *= 4; // 4
	n -= 1;
	if (n % 5) return false;
	n /= 5;
	n *= 4; // 5
	return true;
}

int main() {
	for (int i = 1; i < 1111111; i++) {
		if (can(i)) {
			cout << i << endl;
			break;
		}
	}
	cout << can(19531);
	return 0;
}
