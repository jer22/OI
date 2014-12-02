/*
ID:shijiey1
PROG:zerosum
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[10];
int i = 1;

void print() {
	for (int j = 1; j <= n; j++) {
		printf("%d", j);
		if (arr[j] == 1)
			printf(" ");
		if (arr[j] == 2)
			printf("+");
		if (arr[j] == 3)
			printf("-");
	}
	printf("\n");
}

void dfs(int pos, int sum, int pre) {

	if (pos == n) {
		// printf("%d = ", sum);
		if (!sum)
			print();
		return;
	}
	// " "
	int now = pre * 10 + pos + 1;
	arr[i++] = 1;
	if (arr[i - 2] != 3)
		dfs(pos + 1, sum - pre + now, now);
	else dfs(pos + 1, sum + pre - now, now);
	arr[--i] = 0;
	// +
	arr[i++] = 2;
	dfs(pos + 1, sum + pos + 1, pos + 1);
	arr[--i] = 0;
	// -
	arr[i++] = 3;
	dfs(pos + 1, sum - pos - 1, pos + 1);
	arr[--i] = 0;
}

int main() {
	freopen("zerosum.in", "r", stdin);
	freopen("zerosum.out", "w", stdout);
	scanf("%d", &n);
	dfs(1, 1, 1);

	return 0;
}
