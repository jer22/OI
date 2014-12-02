#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int arr[80][80];
int n, m;
int cow = 0, house = 0;

void visit(int x, int y) {
	arr[x][y] = -1;
	if (arr[x - 1][y] == 1) visit(x - 1, y);
	if (arr[x + 1][y] == 1) visit(x + 1, y);
	if (arr[x][y - 1] == 1) visit(x, y - 1);
	if (arr[x][y + 1] == 1) visit(x, y + 1);
}

int main() {
	freopen("satel.in", "r", stdin);
	freopen("satel.out", "w", stdout);
	scanf("%d %d\n", &n, &m);
	memset(arr, 0, sizeof(arr));
	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%c", &c);
			arr[i][j] = c == '.' ? 0 : 1;
		}
		getchar();
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!arr[i][j]) {
				if (arr[i + 1][j] == 1 && arr[i][j + 1] == 1 && arr[i + 1][j + 1] == 1) {
					cow++;
					visit(i + 1, j + 1);
				}
				if (arr[i + 1][j] == 1 && arr[i][j - 1] == 1 && arr[i + 1][j - 1] == 1) {
					cow++;
					visit(i + 1, j - 1);
				}
				if (arr[i - 1][j] == 1 && arr[i][j + 1] == 1 && arr[i - 1][j + 1] == 1) {
					cow++;
					visit(i - 1, j + 1);
				}
				if (arr[i - 1][j] == 1 && arr[i][j - 1] == 1 && arr[i - 1][j - 1] == 1) {
					cow++;
					visit(i - 1, j - 1);
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j] == 1 && !arr[i - 1][j] && !arr[i][j - 1])
				house++;
		}
	}
	printf("%d\n%d\n", house, cow);
	return 0;
}
