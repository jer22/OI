#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;

int n, m;
map<string, int> has;
char op[MAXN][5];
int num[MAXN][1005];
int fom[MAXN][2];
int ans[MAXN];

int cal(int bi, int c) {
	int ans = 0;
	num[0][bi] = c;
	for (int i = 1; i <= n; i++) {
		if (op[i][0] == 'A') {
			num[i][bi] = num[fom[i][0]][bi] & num[fom[i][1]][bi];
		} else if (op[i][0] == 'X') {
			num[i][bi] = num[fom[i][0]][bi] ^ num[fom[i][1]][bi];
		} else if (op[i][0] == 'O') {
			num[i][bi] = num[fom[i][0]][bi] | num[fom[i][1]][bi];
		}
			ans += (num[i][bi]);
	}
	return ans;
}

void solve1() {
	for (int i = 0; i < m; i++) {
		if (cal(i, 0) <= cal(i, 1)) {
			cout << 0;
		} else cout << 1;
	}
	cout << '\n';
}

void solve2() {
	for (int i = 0; i < m; i++) {
		if (cal(i, 0) < cal(i, 1)) {
			cout << 1;
		} else cout << 0;
	}
	cout << '\n';
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d %d", &n, &m);
	string s;
	char a[1005], b[1005];
	has["?"] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		scanf("%s%s", op[i], a);
		has[s] = i;
		if (a[0] == '0' || a[0] == '1') {
			for (int j = 0; j < m; j++)
				num[i][j] = a[j] - '0';
		} else {
			scanf("%s%s", op[i], b);
			fom[i][0] = has[a];
			fom[i][1] = has[b];
		}
		// cout << op[i] << endl;
	}
	solve1();
	solve2();

	return 0;
}
