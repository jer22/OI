#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int n, m;
char arr[111][111];
int pre[111];

bool bad(int j) {
	for (int i = 1; i < n; i++) {
		if (arr[i][j] < arr[i - 1][j] && !pre[i]) return true;
	}
	for (int i = 1; i < n; i++) {
		if (arr[i][j] > arr[i - 1][j]) pre[i] = 1;
	}
	return false;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", arr[i]);
	}
	int ans = 0;
	for (int j = 0; j < m; j++) {
		if (bad(j)) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
