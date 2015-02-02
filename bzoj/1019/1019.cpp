#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n;
string prio[8];
long long f[4][32];
int g[4][32];
int main() {
	freopen("1019.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= 6; i++)
		cin >> prio[i];
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 6; j++) {
			if (prio[j][0] == 'A' + i - 1) {
				f[i][1] = 1;
				g[i][1] = prio[j][1] - 'A' + 1;
				break;
			}
		}
	}
	for (int i = 2; i <= n; i++) {
		for (int x = 1; x <= 3; x++) {
			int y = g[x][i - 1];
			int z = 6 - y - x;
			f[x][i] = f[x][i - 1] + 1;
			if (g[y][i - 1] == z) {
				g[x][i] = z;
				f[x][i] += f[y][i - 1];
			} else {
				g[x][i] = y;
				f[x][i] += f[y][i - 1] + 1 + f[x][i - 1];
			}
		}
	}
	cout << f[1][n] << endl;
	return 0;
}
