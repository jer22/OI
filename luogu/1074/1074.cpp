#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXTIME 10000000

using namespace std;

int arr[11][11];
int score[11][11];
int vertical[11][11];
int horizontal[11][11];
int squared[11][11];
int point = 0;
int highPoint = 0;
int maxStep = 0;
int times = 0;

/**
	数独的每一格的分数
	666666666
	677777776
	678888876
	678999876
	6789109876
	678999876
	678888876
	677777776
	666666666

*/
void initScore() {
	for (int i = 1; i <= 9; i++) {
		score[1][i] = 6;
		score[i][1] = 6;
		score[9][i] = 6;
		score[i][9] = 6;
	}
	for (int i = 2; i <= 8; i++) {
		score[2][i] = 7;
		score[i][2] = 7;
		score[8][i] = 7;
		score[i][8] = 7;
	}
	for (int i = 3; i <= 7; i++) {
		score[3][i] = 8;
		score[i][3] = 8;
		score[7][i] = 8;
		score[i][7] = 8;
	}
	for (int i = 4; i <= 6; i++) {
		score[4][i] = 9;
		score[i][4] = 9;
		score[6][i] = 9;
		score[i][6] = 9;
	}
	score[5][5] = 10;
}

/**
	(x, y)的位置上是否可以放置值为num的数字
*/
bool canPut(int x, int y, int num) {
	if (horizontal[x][num] || vertical[y][num] || squared[(x - 1) / 3 * 3 + (y - 1) / 3 + 1][num]) {
		return false;
	}
	return true;
}

// step:已经填的数字的个数
void dfs(int step) {
	times++;
	if (times > MAXTIME) {
		printf("%d\n", highPoint);
		exit(0);
	}
	maxStep = max(step, maxStep);
	if (step == 81) {
		return;
	}
	int maxBlockVertical;
	int t = 0;
	for (int i = 1; i <= 9; i++) {
		if (vertical[i][0] == 9) {
			continue;
		}
		if (vertical[i][0] >= t) {
			t = vertical[i][0];
			maxBlockVertical = i;
		}
	}
	for (int i = 9; i >= 1; i--) {
		if (!arr[i][maxBlockVertical]) {
			
			for (int num = 1; num <= 9; num++) {
				if (canPut(i, maxBlockVertical, num)) {
					
					arr[i][maxBlockVertical] = num;
					horizontal[i][num] = 1;
					vertical[maxBlockVertical][num] = 1;
					vertical[maxBlockVertical][0]++;
					squared[(i - 1) / 3 * 3 + (maxBlockVertical - 1) / 3 + 1][num] = 1;
					point += arr[i][maxBlockVertical] * score[i][maxBlockVertical];
					highPoint = max(highPoint, point);
					dfs(step + 1);
					point -= arr[i][maxBlockVertical] * score[i][maxBlockVertical];
					horizontal[i][num] = 0;
					vertical[maxBlockVertical][num] = 0;
					vertical[maxBlockVertical][0]--;
					squared[(i - 1) / 3 * 3 + (maxBlockVertical - 1) / 3 + 1][num] = 0;
					arr[i][maxBlockVertical] = 0;
				}
			}
			return;
		}
	}
}

int main() {
	freopen("1074.in", "r", stdin);
	int step = 0;
	initScore();
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			scanf("%d", &arr[i][j]);
			// 初始分数
			point += arr[i][j] * score[i][j];
			if (arr[i][j]) {
				horizontal[i][arr[i][j]] = 1;
				vertical[j][arr[i][j]] = 1;
				vertical[j][0]++;
				squared[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][arr[i][j]] = 1;
				step++;
			}
		}
	}
	maxStep = step;
	highPoint = point;

	dfs(step);

	if (maxStep < 81) {
		printf("-1\n");
	} else {
		printf("%d\n", highPoint);
	}
	return 0;
}
