#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m, q;
int arr[1010][1010];
int sum[1010][1010];
int main() {
	freopen("1003.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &m, &q)) {
		memset(arr, 0, sizeof(arr));
		memset(sum, 0, sizeof(sum));
		char c = getchar();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%c", &c);	
				if (c == 'X') arr[i][j] = 1;
				sum[i][j] = sum[i][j - 1] + arr[i][j];
			}
			getchar();
		}
		if (q >= 40) {

		}

		
	}

	return 0;
}
