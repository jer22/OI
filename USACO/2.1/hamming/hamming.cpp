/*
ID:shijiey1
PROG:hamming
LANG:C++
*/

/*
数据范围很小所以dfs。
每次从当前的最大数+1向上枚举，与之前的所有数字比较，如果可以则记录。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int n, b, d;
vector<int> ans;

bool cmp(int a, int b) {
	int cnt = 0;
	while (a || b) {
		cnt += ((a & 1) ^ (b & 1));
		a >>= 1;
		b >>= 1;
	}
	return cnt >= d;
}

void dfs(int i, int step) {
	ans.push_back(i);
	if (step == n) {
		for (int j = 0; j < ans.size(); j++) {
			if (!((j + 1) % 10 - 1) && j) printf("\n");
			else if (j) printf(" ");
			printf("%d", ans[j]);
		}
		printf("\n");
		exit(0);
	}
	
	for (int j = i + 1; j < 1 << b; j++) {
		bool flag = true;
		for (int k = 0; k < ans.size(); k++) {
			flag = cmp(ans[k], j);
			if (!flag) break;
		}
		if (flag) {
			dfs(j, step + 1);
			break;
		}
	}

}

int main() {
	freopen("hamming.in", "r", stdin);
	freopen("hamming.out", "w", stdout);
	scanf("%d %d %d", &n, &b, &d);
	dfs(0, 1);

	return 0;
}
