#include <bits/stdc++.h>

using namespace std;

int n;
string str;
int main() {
	cin >> n;
	cin >> str;
	for (int i = 0; i < n; i++) {
		if (i + 2 < n && str[i] == 'o' && str[i + 1] == 'g' && str[i + 2] == 'o') {
			cout << "***";
			int j = i + 3;
			while (j + 1 < n && str[j] == 'g' && str[j + 1] == 'o') j += 2;
			i = j - 1;
		} else cout << str[i];
	}
	cout << endl;
	return 0;
}
