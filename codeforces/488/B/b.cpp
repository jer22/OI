#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int input[5];
int ans[5];

bool solve() {
	if (!n) {
		cout << "YES" << endl;
		cout << 1 << endl << 1 << endl << 3 << endl << 3 << endl;
		return true;
	}
	if (n == 1) {
		cout << "YES" << endl;
		cout << input[1] << endl << input[1] * 3 << endl << input[1] * 3 << endl;
		return true;
	}
	if (n == 2) {
		if (input[2] % 3) {
			if (input[1] * 3 < input[2]) return false;
			cout << "YES" << endl;
			ans[1] = input[1];
			ans[4] = input[1] * 3;
			int t = 4 * ans[1] - input[2];
			cout << ans[4] << endl << t << endl;
			return true;
		} else {
			if (input[2] / 3 > input[1]) return false;
			cout << "YES" << endl;
			ans[1] = input[2] / 3;
			int t = 4 * ans[1] - input[1];
			cout << ans[1] << endl << t << endl;
			return true;
		}
	}
	if (n == 3) {
		if (input[3] % 3) {
			if (input[1] * 3 < input[3]) return false;
			for (int i = 1; i <= 3; i++) ans[i] = input[i];
			ans[4] = ans[1] * 3;
			if (ans[1] << 2 != ans[2] + ans[3]) return false;
			cout << "YES" << endl << ans[4] << endl;
			return true;
		} else {
			if (input[3] / 3 > input[1]) return false;
			if (input[3] / 3 == input[1]) {
				cout << "YES" << endl;
				cout << input[1] * 4 - input[2] << endl;
				return true;
			}
			ans[1] = input[3] / 3;
			ans[4] = input[3];
			ans[2] = input[1];
			ans[3] = input[2];
			if (4 * ans[1] != ans[2] + ans[3]) return false;
			cout << "YES" << endl << ans[1] << endl;
			return true;
		}
	}
	if (n == 4) {
		for (int i = 1; i <= 4; i++) ans[i] = input[i];
		if (4 * ans[1] == ans[2] + ans[3]) {
			cout << "YES" << endl;
			return true;
		}
		else return false;
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> input[i];
	}
	sort(input + 1, input + n + 1);
	if (!solve()) {
		cout << "NO" << endl;
	}

	return 0;
}
