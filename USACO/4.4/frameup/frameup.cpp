/*
ID:shijiey1
LANG:C++
PROG:frameup
*/

/*
用1~26表示每种字母
统计每种字母的最小与最大的x与y坐标，这样就知道了每个矩形的边框。
从最上层开始dfs，找到当前所有边框上都是同样数字的矩形，则这个矩形一定是最上层的，继续dfs。
每次dfs找到一个矩形时，将该矩形的边框上的所有数字设为负数，负数可以看作是任何一种数字。回溯时再还原。
dfs到最后一层时记录答案，最后排序输出。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
int arr[35][35];
int x1[28];
int y1[28];
int x2[28];
int y2[28];
int T;
int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

void init() {
	memset(x1, -1, sizeof(x1));
	memset(y1, -1, sizeof(y1));
	memset(x2, -1, sizeof(x2));
	memset(y2, -1, sizeof(y2));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!arr[i][j]) continue;
			x1[arr[i][j]] = min(x1[arr[i][j]], i);
			y1[arr[i][j]] = min(y1[arr[i][j]], j);
			x2[arr[i][j]] = max(x2[arr[i][j]], i);
			y2[arr[i][j]] = max(y2[arr[i][j]], j);
		}
	}
	for (int i = 1; i <= 26; i++)
		if (x1[i] != -1) T++;
}

int done[28];
vector<int> ans;
vector<vector<int> > last;
void dfs(int step) {
	if (step == T) {
		last.push_back(ans);
		return;
	}
	for (int i = 1; i <= 26; i++) {

		if (x1[i] == -1 || done[i]) continue;
		bool flag = true;
		for (int j = x1[i]; j <= x2[i]; j++) {
			if (arr[j][y1[i]] != i && arr[j][y1[i]] > 0 || (arr[j][y2[i]] != i && arr[j][y2[i]] > 0)) {
				flag = false;
				break;
			}
		}
		if (!flag) continue;
		for (int j = y1[i]; j <= y2[i]; j++) {
			if (arr[x1[i]][j] != i && arr[x1[i]][j] > 0 || (arr[x2[i]][j] != i && arr[x2[i]][j] > 0)) {
				flag = false;
				break;
			}
		}
		if (!flag) continue;

		for (int j = x1[i]; j <= x2[i]; j++) {
			if (arr[j][y1[i]] == i) {
				arr[j][y1[i]] = -i - 1;
			}
			if (arr[j][y2[i]] == i) {
				arr[j][y2[i]] = -i - 1;
			}
		}
		for (int j = y1[i]; j <= y2[i]; j++) {
			if (arr[x1[i]][j] == i) {
				arr[x1[i]][j] = -i - 1;
			}
			if (arr[x2[i]][j] == i) {
				arr[x2[i]][j] = -i - 1;
			}
		}
		done[i] = 1;
		ans.push_back(i);
		dfs(step + 1);
		ans.pop_back();
		done[i] = 0;
		for (int j = x1[i]; j <= x2[i]; j++) {
			if (arr[j][y1[i]] == -i - 1) {
				arr[j][y1[i]] = i;
			}
			if (arr[j][y2[i]] == -i - 1) {
				arr[j][y2[i]] = i;
			}
		}
		for (int j = y1[i]; j <= y2[i]; j++) {
			if (arr[x1[i]][j] == -i - 1) {
				arr[x1[i]][j] = i;
			}
			if (arr[x2[i]][j] == -i - 1) {
				arr[x2[i]][j] = i;
			}
		}
	}
}

int cmp(vector<int> a, vector<int> b) {
	for (int i = T - 1; i >= 0; i--) {
		if (a[i] != b[i])
			return a[i] < b[i];
	}
	return 0;
}

int main() {
	freopen("frameup.in", "r", stdin);
	freopen("frameup.out", "w", stdout);
	scanf("%d %d\n", &n, &m);
	char c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%c", &c);
			if (c != '.') arr[i][j] = c - 'A' + 1;
		}
		getchar();
	}
	init();
	dfs(0);
	sort(last.begin(), last.end(), cmp);
	for (int i = 0; i < last.size(); i++) {
		ans = last[i];
		for (int j = T - 1; j >= 0; j--) {
			printf("%c", ans[j] + 'A' - 1);
		}
		printf("\n");
	}

	return 0;
}
