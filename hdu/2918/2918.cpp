#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define p(i, j) (((i) * 3) + (j))

using namespace std;

int wors;
char str[11];
int arr[10];
int op[8][4] = {
	{0, 1, 4, 3}, {3, 4, 1, 0},
	{1, 2, 5, 4}, {1, 4, 5, 2},
	{3, 4, 7, 6}, {6, 7, 4, 3},
	{4, 5, 8, 7}, {4, 7, 8, 5}
};

int geth() {
	int ans = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ans += abs(i - arr[p(i, j)] / 3) + abs(j - arr[p(i, j)] % 3);
	return (ans + 3) / 4;
}

void move(int k) {
	int t = arr[op[k][0]];
	for (int i = 0; i < 3; i++)
		arr[op[k][i]] = arr[op[k][i + 1]];
	arr[op[k][3]] = t;
}

bool dfs(int dep, int pre, int now) {
	int h = geth();
	if (!h) return true;
	if (now + h > dep) return false;
	for (int i = 0; i < 8; i++) {
		if (pre == (i ^ 1)) continue;
		move(i);
		if (dfs(dep, i, now + 1)) return true;
		move(i ^ 1);
	}
	return false;
}

int main() {
	freopen("2918.in", "r", stdin);
	int cas = 0;
	while (~scanf("%s", str)) {
		if (str[1] == '0') break;
		cas++;
		wors = str[0] - '0';
		for (int i = 0; i < 9; i++)
			arr[i] = str[i + 1] - '0' - 1;
		int best = geth();
		while (best <= wors && !dfs(best, 8, 0)) best++;
		if (best > wors) best = -1;
		printf("%d. %d\n", cas, best);
	}


	return 0;
}
