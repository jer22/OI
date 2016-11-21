#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int arr[25];
int op[8][7] = {
	{0, 2, 6, 11, 15, 20, 22},
	{1, 3, 8, 12, 17, 21, 23},
	{10, 9, 8, 7, 6, 5, 4},
	{19, 18, 17, 16, 15, 14, 13},
	{23, 21, 17, 12, 8, 3, 1},
	{22, 20, 15, 11, 6, 2, 0},
	{13, 14, 15, 16, 17, 18, 19},
	{4, 5, 6, 7, 8, 9, 10}
};
int ref[] = {5, 4, 7, 6, 1, 0, 3, 2, 8};
int mid[] = {6, 7, 8, 11, 12, 15, 16, 17};

int geth() {
	int cnt[4] = {0, 0, 0, 0};
	for (int i = 0; i < 8; i++)
		cnt[arr[mid[i]]]++;
	return 8 - max(cnt[1], max(cnt[2], cnt[3]));
}

void move(int k) {
	int t = arr[op[k][0]];
	for (int i = 0; i < 6; i++)
		arr[op[k][i]] = arr[op[k][i + 1]];
	arr[op[k][6]] = t;
}

int ans[1005];
bool dfs(int dep, int now, int pre) {
	int h = geth();
	if (!h) return true;
	if (now + h > dep) return false;
	for (int i = 0; i < 8; i++) {
		if (i == ref[pre]) continue;
		move(i);
		ans[now] = i;
		if (dfs(dep, now + 1, i)) return true;
		move(ref[i]);
	}
	return false;
}

int main() {
	freopen("1667.in", "r", stdin);
	while (~scanf("%d", &arr[0])) {
		if (!arr[0]) break;
		for (int i = 1; i < 24; i++)
			scanf("%d", &arr[i]);
		int best = geth();
		if (!best) printf("No moves needed");
		else {
			while (!dfs(best, 0, 8)) best++;
			for (int i = 0; i < best; i++)
				printf("%c", ans[i] + 'A');
		}
		printf("\n%d\n", arr[6]);
	}


	return 0;
}
