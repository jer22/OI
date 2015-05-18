#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int T;
int n;
bool arr[20005];
map<string, int> vis;
string str[20005];

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int main() {
	freopen("1002.in", "w", stdout);
	

	return 0;
}
