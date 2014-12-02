/*
ID:shijiey1
PROG:namenum
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

string dict[5000];
string num;
char letter[10][3] = {{},{}, {'A','B','C'}, {'D','E','F'}, {'G','H','I'}
	, {'J','K','L'}, {'M','N','O'}, {'P','R','S'}, {'T','U','V'}, {'W','X','Y'}};
int n = 0;

bool contains(char c, int i) {
	return letter[i][0] == c || letter[i][1] == c || letter[i][2] == c;
}

int main() {
	freopen("namenum.out", "w", stdout);
	freopen("namenum.in", "r", stdin);
	cin >> num;
	freopen("dict.txt", "r", stdin);
	while (cin >> dict[n++]);
	bool has = false;
	for (int i = 0; i < n; i++) {
		if (dict[i].size() != num.size()) continue;
		bool flag = false;
		for (int j = 0; j < num.size(); j++) {
			if (!contains(dict[i][j], num[j] - '0')) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			cout << dict[i] << endl;
			has = true;
		}
	}
	if (!has) {
		printf("NONE\n");
	}
	return 0;
}
