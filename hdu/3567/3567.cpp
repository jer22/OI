#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

#define p(i, j) (((i) * 3) + (j))

using namespace std;

int T;
int arr[10], despos[10], spos;

int cantor(int s[]) {
	static int fac[]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	int sum = 0;
	for (int i = 0; i < 9; i++) {
		int num = 0;
		for (int j = i + 1; j < 9; j++)
		if (s[j] < s[i]) num++;
		sum += (num * fac[9 - i - 1]);
	}
	return sum + 1;
}

int get_h(){
	int ans = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (arr[p(i, j)])
				ans += abs(i - despos[arr[p(i, j)]] / 3) + abs(j - despos[arr[p(i, j)]] % 3);
	return ans;
}

char op[4] = {'d', 'l', 'r', 'u'};
int dir[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
int steps[100];
bool dfs(int dep, int pos, int pre, int now) {
	int h = get_h();
	// cout << h << endl;
	if (!h) return true;
	if (now + h > dep) return false;

	int x = pos / 3;
	int y = pos % 3;
	for (int i = 0; i < 4; i++) {
		if (i == 3 - pre) continue;
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (nx < 0 || nx > 2 || ny < 0 || ny > 2) continue;
		// cout << i << endl;
		swap(arr[pos], arr[p(nx, ny)]);
		steps[now] = i;
		if (dfs(dep, p(nx, ny), i, now + 1)) return true;
		swap(arr[pos], arr[p(nx, ny)]);
	}
	return false;
}

char str[10];
int main() {
	freopen("3567.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%s", str);
		for (int i = 0; i <= 8; i++) {
			if (str[i] == 'X') arr[i] = 0, spos = i;
			else arr[i] = str[i] - '0';
		}
		scanf("%s", str);
		for (int i = 0; i <= 8; i++) {
			if (str[i] == 'X') despos[0] = i;
			else despos[str[i] - '0'] = i;
		}
		int ans = get_h();

		// cout << dfs(19, spos, -1, 0);
		while (!dfs(ans, spos, -1, 0)) {
			ans++;
		}
		printf("Case %d: %d\n", cas, ans);
		for (int i = 0; i < ans; i++)
			printf("%c", op[steps[i]]);
		printf("\n");
	}


	return 0;
}
