#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int pos[35][35][35];
char str[500005];
int main() {
	freopen("d.in", "r", stdin);
	str[0] = 'a';
	str[1] = 'a';
	str[2] = 'a';
	for (int i = 3; i < 456976; i++) {
		int a = str[i - 3] - 'a' + 1;
		int b = str[i - 2] - 'a' + 1;
		int c = str[i - 1] - 'a' + 1;
		pos[a][b][c]++;
		if (pos[a][b][c] > 26) {
			cout << i << endl;
			return 0;
		}
		char d = pos[a][b][c] - 1 + 'a';
		str[i] = d;
	}
	int n;
	// while (~scanf("%d", &n)) {
	// 	if (n > 456976) {
	// 		printf("Impossible\n");
	// 		continue;
	// 	}
	// 	for (int i = 0; i < n; i++)
	// 		printf("%c", str[i]);
	// 	printf("\n");
	// }

	return 0;
}
