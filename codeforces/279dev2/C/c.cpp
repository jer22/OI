#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string s;
int n;
int a, b;
int arr[1000010];
int main() {
	cin >> s;
	cin >> a >> b;
	n = s.size();
	int t = 0;
	for (int i = 0; i < n - 1; i++) {
		t = (t * 10 + s[i] - '0') % a;
		arr[i] = t;
	}
	t = 0;
	int base = 1;
	for (int i = n - 1; i >= 1; i--) {
		t = ((s[i] - '0') * base + t) % b;
		base = base * 10 % b;
		if (s[i] != '0' && !t && !arr[i - 1]) {
			cout << "YES" << endl;
			cout << s.substr(0, i) << endl;
			cout << s.substr(i, n - i) << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
	return 0;
}
