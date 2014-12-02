#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;


int n;
int cnt = 0;
int arr[15][15];
int a1[100];
int a2[100];
int a3[100];

void print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (arr[i][j]) {
				printf("%d", j);
				if (i != n) {
					printf(" ");
				}
				break;
			}
		}
	}
	printf("\n");
}

bool canPut(int x, int y) {
	if (a1[y]) {
		return false;
	}
	if (a2[x + y]) {
		return false;
	}
	if (a3[x - y + 20]) {
		return false;
	}
	return true;
}

void dfs(int x) {
	if (x == n + 1) {
		cnt++;
		if (cnt <= 3)
			print();
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (canPut(x, i)) {
			arr[x][i] = 1;
			a1[i] = 1;
			a2[x + i] = 1;
			a3[x - i + 20] = 1;
			dfs(x + 1);
			a1[i] = 0;
			a2[x + i] = 0;
			a3[x - i + 20] = 0;
			arr[x][i] = 0;
		}
	}
}

int main() {
	freopen("1219.in", "r", stdin);
	scanf("%d", &n);

	dfs(1);
	printf("%d\n", cnt);
	return 0;
}
