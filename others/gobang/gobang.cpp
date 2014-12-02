#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char arr[15][15];
int n;
bool canWin(int i, int j) {
	int cnt = 0;
	for (int k = j - 1; k >= 0; k--) {
		if (arr[i][k] == '0') cnt++;
		else break;
	}
	for (int k = j + 1; k < n; k++) {
		if (arr[i][k] == '0') cnt++;
		else break; 
	}
	if (cnt >= 4) return true;
	cnt = 0;
	for (int k = i - 1; k >= 0; k--) {
		if (arr[k][j] == '0') cnt++;
		else break;
	}
	for (int k = i + 1; k < n; k++) {
		if (arr[k][j] == '0') cnt++;
		else break;
	}
	if (cnt >= 4) return true;
	cnt = 0;
	for (int k = i - 1, l = j - 1; k >= 0, l >= 0; k--, l--) {
		if (arr[k][l] == '0') cnt++;
		else break;
	}
	for (int k = i + 1, l = j + 1; k < n, l < n; k++, l++) {
		if (arr[k][l] == '0') cnt++;
		else break;
	}
	if (cnt >= 4) return true;
	cnt = 0;
	for (int k = i - 1, l = j + 1; k >= 0, l < n; k--, l++) {
		if (arr[k][l] == '0') cnt++;
		else break;
	}
	for (int k = i + 1, l = j - 1; k < n, l >= 0; k++, l--) {
		if (arr[k][l] == '0') cnt++;
		else break;
	}
	if (cnt >= 4) return true;
	cnt = 0;
	return false;
}

int main() {
	freopen("gobang.in", "r", stdin);
	freopen("gobang.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", arr[i]);
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == '*' && canWin(i, j)) {
				cnt++;
				printf("%d %d\n", i, j);
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}
