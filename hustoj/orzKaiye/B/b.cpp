#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
char a[200005], b[200005];
bool vis[128][128];
int main() {
	// freopen("b.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s%s", a, b);
	int tot = 0;
	int i1 = -1, i2 = -1;
	char an1 = '.', an2 = '.';
	for (int i = 0; i < n; i++) {
		char x = a[i], y = b[i];
		vis[x][y] = 1;
		if (x != y) tot++;
		if (x != y && vis[y][x]) {
			an1 = y, an2 = x;
		}
	}
	if (an1 != '.') {
		for (int i = 0; i < n; i++) {
			if (a[i] == an1 && b[i] == an2) i1 = i;
			else if (a[i] == an2 && b[i] == an1) i2 = i;
		}
		if (i1 != -1 && i2 != -1) {
			printf("%d\n", tot - 2);
			printf("%d %d\n", i1 + 1, i2 + 1);
			return 0;
		}
	}
	for (int c = 'a'; c <= 'z'; c++) {
		i1 = -1, i2 = -1;
		for (int i = 0; i < n; i++) {
			// if (a[i] == b[i]) continue;
			if (a[i] == c && a[i] != b[i]) i1 = i;
			if (b[i] == c && a[i] != b[i]) i2 = i;
			if (i1 != -1 && i2 != -1 && i1 != i2 && a[i1] != b[i1] && a[i2] != b[i2]) {
				printf("%d\n", tot - 1);
				printf("%d %d\n", i1 + 1, i2 + 1);
				return 0;
			}
		}
	}
	printf("%d\n", tot);
	printf("-1 -1\n");
	
	return 0;
}
