#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string str;
string a = "Apple", b = "iPhone", c = "iPod", d = "iPad";
string sony = "Sony";
int main() {
	freopen("a.in", "r", stdin);
	while (cin >> str) {
		for (int i = 0; i < str.size(); i++) {
			if (str.substr(i, 5) == a) printf("MAI MAI MAI!\n");
			if (str.substr(i, 6) == b) printf("MAI MAI MAI!\n");
			if (str.substr(i, 4) == c) printf("MAI MAI MAI!\n");
			if (str.substr(i, 4) == d) printf("MAI MAI MAI!\n");
			if (str.substr(i, 4) == sony) printf("SONY DAFA IS GOOD!\n");
		}
	}
	return 0;
}
