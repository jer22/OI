#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

struct Node{
	int a[10];
};

int T;
Node s;
int equs[40][3], tot = 0;
int sum[40][9];
int nex[40], neq[6] = {0, 36, 21, 10, 3, 0};

void init() {
	for (int i = 1; i <= 4; i++) {
		for (int j = i; j + i <= 9; j++) {
			tot++;
			equs[tot][0] = i;
			equs[tot][1] = j;
			equs[tot][2] = i + j;
		}
	}
	for (int i = tot; i >= 1; i--) {
		for (int j = 1; j <= 9; j++)
			sum[i][j] = sum[i + 1][j];
		for (int j = 0; j < 3; j++)
			sum[i][equs[i][j]]++;
	}
	for (int i = 1; i <= tot; i++) {
		if (tot - i < 2) nex[i] = 21;
		else if (tot - i < 6) nex[i] = 19;
		else if (tot - i < 12) nex[i] = 15;
		else nex[i] = 9;
	}
}

int best = 0;
int cnt = 0;
void dfs(int step, int now) {
	best = max(best, now);
	if (neq[equs[step][0]] + now <= best) return;
	if (step > tot) return;
	for (int i = step; i <= tot; i++) {
		bool flag = true;
		if (!s.a[equs[i][0]]) {
			dfs(nex[step], now);
			return;
		}
		for (int j = 0; j < 3; j++) {
			if (!s.a[equs[i][j]])
				flag = false;
			s.a[equs[i][j]]--;
		}
		if (flag) {
			dfs(i + 1, now + 1);
			if (equs[i][0] != equs[i][1]) {
				flag = true;
				for (int j = 0; j < 3; j++) {
					if (!s.a[equs[i][j]])
						flag = false;
					s.a[equs[i][j]]--;
				}
				if (flag) dfs(i + 1, now + 2);
				for (int j = 0; j < 3; j++)
					s.a[equs[i][j]]++;
			}
		}
		for (int j = 0; j < 3; j++)
			s.a[equs[i][j]]++;
	}
}

int main() {
	// freopen("5937.in", "r", stdin);
	init();
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		for (int i = 1; i <= 9; i++) {
			scanf("%d", &s.a[i]);
			s.a[i] = min(s.a[i], 17 - i);
		}
		best = 0;
		dfs(1, 0);
		printf("Case #%d: %d\n", cas, best);
	}
	return 0;
}
