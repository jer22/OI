#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
char s[1005][1005];
int cx[1005], cy[1005];
int main() {
	// freopen("b.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '.') continue;
			cx[i]++;
			cy[j]++;
			sum++;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if ((cx[i] + cy[j] - (s[i][j] == '*')) >= sum) {
				cout << "YES" << endl << i << ' ' << j << endl;
				return 0;
			}
		}
	}
	cout << "NO" << endl;
	return 0;
}
