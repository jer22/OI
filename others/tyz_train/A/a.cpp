#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

char str[10000000];
int tot = 0;
int main() {
	freopen("a.in", "r", stdin);
	char c;
	while (~scanf("%c", &c)) {
		if (c >= 'A' && c <= 'Z') c = c + 'a' - 'A';
		str[tot++] = c;
	}
	int ans = 0;
	for (int i = 0; i <= tot; i++) {
		if (str[i] == 'd') {
			if (str[i + 1] == 'o' && str[i + 2] == 'g' && str[i + 3] == 'e') ans++;
		}
	}
	cout << ans << endl;

	return 0;
}
