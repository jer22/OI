#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int canPut;
int arr[20][20];
int a;
int b;
int c;
int maxStep = 0;

bool canGo(int x, int y) {
	return !(canPut & 1 << (x * 15 + y) | (a & (1 << y)) | (b & (1 << (x + y))) | (c & (1 << (x - y + 13))));
}

void dfs(int x) {
	if (x == n + 1) {
		maxStep++;
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (canGo(x, i)) {
			arr[x][i] = 1;
			a = a | (1 << i);
			b = b | (1 << (x + i));
			c = c | (1 << (x - i + 13));
			dfs(x + 1);
			a = a ^ (1 << i);
			b = b ^ (1 << (x + i));
			c = c ^ (1 << (x - i + 13));
			arr[x][i] = 0;
		}
	}
}

int main() {
	freopen("queens.in", "r", stdin);
	freopen("queens.out", "w", stdout);
	scanf("%d", &n);
	char c = getchar();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%c", &c);
			if (c == '.') canPut = canPut | 1 << (i * 15 + j);
		}
		getchar();
	}
	dfs(1);
	printf("%d\n", maxStep);
	return 0;
}
