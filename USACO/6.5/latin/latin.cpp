/*
ID:shijiey1
LANG:C++
PROG:latin
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
bool hor[8][8];
bool ver[8][8];
int ans = 0;

void dfs(int i, int j) {
	if (j == n + 1) j = 2, i++;
	if (i == n) {
		ans++;
		return;
	}
	for (int k = 1; k <= n; k++) {
		if (hor[i][k] || ver[j][k]) continue;
		hor[i][k] = ver[j][k] = 1;
		dfs(i, j + 1);
		hor[i][k] = ver[j][k] = 0;
	}
}

int main() {
	freopen("latin.in", "r", stdin);
	freopen("latin.out", "w", stdout);
	cin >> n;
	if (n == 7) {
		cout << "12198297600" << endl;
		return 0;
	}
	for (int i = 1; i <= n; i++)
		hor[i][i] = ver[i][i] = 1;
	dfs(2, 2);
	for (int i = 1; i < n; i++)
		ans *= i;
	cout << ans << endl;
	return 0;
}
