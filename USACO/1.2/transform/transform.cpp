/*
ID:shijiey1
PROG:transform
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
char origin[12][12];
char target[12][12];
char trans1[12][12];
char trans2[12][12];
char trans3[12][12];
char trans4[12][12];
char trans51[12][12];
char trans52[12][12];
char trans53[12][12];
void init() {
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= n + 1; j++) {
			origin[i][j] = ' ';
			target[i][j] = ' ';
		}
	}
}

int main() {
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);
	scanf("%d\n", &n);
	init();
	bool flag = false;
	if (!(n % 2)) flag = true;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int k = i, l = j;
			if (flag && i > (n >> 1)) k++;
			if (flag && j > (n >> 1)) l++;
			scanf("%c", &origin[k][l]);
		}
		scanf("\n");
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int k = i, l = j;
			if (flag && i > (n >> 1)) k++;
			if (flag && j > (n >> 1)) l++;
			scanf("%c", &target[k][l]);
		}
		scanf("\n");
	}
	if (flag) n++;
	int mid = (n >> 1) + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			trans1[j][n + 1 - i] = origin[i][j];
			trans2[n + 1 - i][n + 1 - j] = origin[i][j];
			trans3[n + 1 - j][i] = origin[i][j];
			trans4[i][n + 1 - j] = origin[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			trans51[j][n + 1 - i] = trans4[i][j];
			trans52[n + 1 - i][n + 1 - j] = trans4[i][j];
			trans53[n + 1 - j][i] = trans4[i][j];
		}
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (trans1[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("1\n");
		return 0;
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (trans2[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("2\n");
		return 0;
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (trans3[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("3\n");
		return 0;
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (trans4[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("4\n");
		return 0;
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (trans51[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("5\n");
		return 0;
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (trans52[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("5\n");
		return 0;
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (trans53[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("5\n");
		return 0;
	}
	flag = true;
	for (int i = 1; i <= n; i++) {
		if (!flag) break;
		for (int j = 1; j <= n; j++) {
			if (origin[i][j] != target[i][j]) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		printf("6\n");
		return 0;
	}
	printf("7\n");
	return 0;
}
