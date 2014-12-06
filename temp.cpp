#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int x1, y, x2, y2;
int arr[11];
int cnt = 0;
int vis[11];

void print() {
	for (int i = 0; i < cnt; i++) {
		if (i) printf(" ");
		printf("%d", arr[i]);
	}
	printf("\n");
}

void dfs(int step) {
	if (step == n + 1) {
		print();
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			arr[cnt++] = i;
			dfs(step + 1);
			arr[--cnt] = 0;
			vis[i] = 0;
		}
	}
}

int main() {
	freopen("temp.in", "r", stdin);
	freopen("temp.out", "w", stdout);
	cin >> n;
	dfs(1);
	return 0;
}
