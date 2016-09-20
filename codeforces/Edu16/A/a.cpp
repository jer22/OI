#include <bits/stdc++.h>

using namespace std;

string s;

bool inc(int a, int b) {
	return (!a || a == 7) && (!b || b == 7);
}

bool inb(int a, int b) {
	return (!a || a == 7) || (!b || b == 7);
}

int main() {
	freopen("a.in", "r", stdin);
	cin >> s;
	int a = s[0] - 'a';
	int b = s[1] - '1';
	if (inc(a, b)) cout << 3 << endl;
	else if (inb(a, b)) cout << 5 << endl;
	else cout << 8 << endl;
	return 0;
}
