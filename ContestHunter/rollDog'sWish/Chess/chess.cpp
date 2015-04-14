#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

char str[100];
int main() {
	freopen("chess.in", "r", stdin);
	int T;
	cin >> T;
	while (T--) {
		scanf("%s", str);
		if (strlen(str) == 1) {
			if (str[0] == '1') printf("1\n");
			else if (str[0] == '2') printf("4\n");
			else printf("-1\n");
		} else {
			printf("-1\n");
		}
	}


	return 0;
}
