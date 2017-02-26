#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
char s[2005][2005];
bool vis[2005][2005];

int solvedown(int x, int y) {
	
	for (int i = x + 2; i <= n; i++) {
		vis[i][y] = 1;
		if (s[i][y] == 'X' && s[i - 1][y] == 'X' && s[i][y + 1] == 'X' && s[i - 1][y + 1] == '.') {
			if (i + 1 < n && s[i][y + 2] == 'X' && s[i + 1][y] == 'X'
				&& s[i + 1][y + 1] == 'X' && s[i + 1][y + 2] == '.'
				&& s[i + 2][y] == 'X' && s[i + 2][y + 1] == 'X')
				continue;
			return i;
		}
	}
	// cout << "fuck" << endl;
	return -1;
}

int solveright(int x, int y) {
	for (int i = y + 2; i <= m; i++) {
		vis[x][i] = 1;
		if (s[x][i] == 'X' && s[x][i - 1] == 'X' && s[x + 1][i] == 'X' && s[x + 1][i - 1] == '.') {
			if (i + 1 < m && s[x][i + 1] == 'X' && s[x + 1][i + 1] == 'X'
				&& s[x + 2][i] == 'X' && s[x + 2][i + 1] == '.'
				&& s[x][i + 2] == 'X' && s[x + 1][i + 2] == 'X')
				continue;
			return i;
		}
	}
	// cout << "shit" << endl;
	return -1;
}

struct Node {
	int a, b, c, d;
};

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", s[i] + 1);
	// solvedown(1, 1);
	vector<Node> ans;
	for (int i = 1; i + 2 <= n; i++) {
		for (int j = 1; j + 2 <= m; j++) {
			if (vis[i][j] || vis[i + 1][j] || vis[i][j + 1]) continue;
			if (s[i][j] == 'X' && s[i + 1][j] == 'X' && s[i][j + 1] == 'X' && s[i + 1][j + 1] == '.') {
				// cout << i << ' ' << j << ' ';
				vis[i][j] = vis[i + 1][j] = vis[i][j + 1] = 1;
				int a = solvedown(i, j);
				int b = solveright(i, j);
				if (a == -1 || b == -1) {
					// cout << "fuck you bitch" << endl;
					while (1);
				}
				for (int k = i; k <= a; k++)
					vis[k][b] = 1;
				for (int k = j; k <= b; k++)
					vis[a][k] = 1;
				// cout << a << ' ' << b << endl;
				ans.push_back((Node){i, j, a, b});
			}
		}
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i].a << ' ' << ans[i].b << ' ' << ans[i].c << ' ' << ans[i].d << endl;
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= m; j++) {
	// 		cout << vis[i][j];
	// 	}
	// 	cout << endl;
	// }

	return 0;
}
