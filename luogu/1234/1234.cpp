#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
char arr[1010][1010];
int main() {
	freopen("1234.in", "r", stdin);
	scanf("%d %d\n", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%c", &arr[i][j]);
		}
		getchar();
	}
	for (int i = 0; i <= n; i++) {
		arr[i][0] = '0';
	}
	for (int i = 0; i <= m; i++) {
		arr[0][i] = '0';
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j] == 'h') {
				if (i - 3 >= 1 && arr[i - 1][j] == 'e' && arr[i - 2][j] == 'h' && arr[i - 3][j] == 'e') {
					cnt++;
				}
				if (i + 3 <= n && arr[i + 1][j] == 'e' && arr[i + 2][j] == 'h' && arr[i + 3][j] == 'e') {
					cnt++;
				}
				if (j - 3 >= 1 && arr[i][j - 1] == 'e' && arr[i][j - 2] == 'h' && arr[i][j - 3] == 'e') {
					cnt++;
				}
				if (j + 3 <= m && arr[i][j + 1] == 'e' && arr[i][j + 2] == 'h' && arr[i][j + 3] == 'e') {
					cnt++;
				}
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}

