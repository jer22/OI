#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n;
string str[11];
int len;
int main() {
	scanf("%d", &n);
	cin >> str[0];
	len = str[0].size();
	str[0] += str[0];
	int siz = len << 1;
	for (int i = 1; i <= 9; i++) {
		str[i] = str[0];
		for (int j = 0; j < siz; j++) {
			str[i][j] = (str[0][j] - '0' + i) % 10 + '0';
		}
	}
	string ans = str[0].substr(0, len);
	string temp;
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j < len; j++) {
			temp = str[i].substr(j, len);
			if (temp < ans) ans = temp;
		}
	}
	cout << ans << endl;
	return 0;
}
