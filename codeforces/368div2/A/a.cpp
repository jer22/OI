#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
char c[3];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n >> m;
	bool flag = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%s", c);
			if ((c[0] != 'B') && (c[0] != 'W') && (c[0] != 'G'))
				flag = false;
		}
	}
	if (flag) cout << "#Black&White" << endl;
	else cout << "#Color" << endl;


	return 0;
}
