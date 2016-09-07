#include <bits/stdc++.h>

using namespace std;

string s;
int main() {
	freopen("c.in", "r", stdin);
	cin >> s;
	int len = s.size();
	int idx1 = len, idx2 = len;
	for (int i = 0; i < len; i++) {
		if (s[i] != 'a') {
			idx1 = i;
			break;
		} 
	}
	if (idx1 == len) {
		for (int i = 0; i < len - 1; i++)
			cout << 'a';
		cout << 'z' << endl;
		return 0;
	}
	for (int i = idx1 + 1; i < len; i++) {
		if (s[i] == 'a') {
			idx2 = i;
			break;
		}
	}
	for (int i = 0; i < idx1; i++) {
		cout << 'a';
	}
	for (int i = idx1; i < idx2; i++) {
		printf("%c", s[i] - 1);
	}
	for (int i = idx2; i < len; i++)
		cout << s[i];
	cout << endl;


	return 0;
}
