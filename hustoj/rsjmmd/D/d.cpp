#include <bits/stdc++.h>

using namespace std;

string str;
char s[100005];
int top = 0;
int main() {
	freopen("d.in", "r", stdin);
	cin >> str;

	for (int i = 0; i < str.length(); i++) {
		s[++top] = str[i];
		while (top > 1 && s[top] == s[top - 1]) top -= 2;
	}
	if (!top) cout << "Yes" << endl;
	else cout << "No" << endl;

	return 0;
}
