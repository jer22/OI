/*
ID:shijiey1
PROG:concom
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm> 

using namespace std;

int m;
int n = 0;
int arr[110][110];
int con[110][110];
int main() {
	freopen("concom.in", "r", stdin);
	freopen("concom.out", "w", stdout);
	memset(arr, 0, sizeof(arr));
	memset(con, 0, sizeof(con));
	scanf("%d", &m);
	int a, b, c;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		n = max(n, max(a, b));
		arr[a][b] = c;
		if (c > 50) con[a][b] = 1;
	}
	for (int i = 1; i <= n; i++) {
		con[i][i] = 1;
	}
	while (true) {
		int flag = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) 
			if (!con[i][j])
			{
				int t = 0;
				for (int k = 1; k <= n; k++) {
					if (con[i][k])
						t += arr[k][j];
				}
				// printf("%d %d %d\n", i, j, t);
				if (t > 50 && !con[i][j])
				{
					flag = 0;
					con[i][j] = 1;
				}
			}
		}
		if (flag) break;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (con[i][j] && (i != j)) {
				printf("%d %d\n", i, j);
			}
		}
	}

	return 0;
}
