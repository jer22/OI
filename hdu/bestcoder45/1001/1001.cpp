#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
long long n;

int solve() {
	int cnt = 0;
	bool flag = false;
	while (n) {
		if (n & 1) {
			if (!flag) cnt++;
			flag = 1;
		} else flag = 0;
		n >>= 1;
	}
	return cnt;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		cin >> n;
		printf("%d\n", solve());
	}
	return 0;
}
