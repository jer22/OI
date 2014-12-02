/*
ID:shijiey1
PROG:crypt1
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

int n;
int arr[10];
map<int, int> exist;

bool contains(int a) {
	while (a) {
		if (!exist[a % 10]) {
			return false;
		}
		a /= 10;
	}
	return true;
}

int main() {
	freopen("crypt1.in", "r", stdin);
	freopen("crypt1.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		exist[arr[i]] = 1;
	}
	int cnt = 0;
	for (int i = 111; i <= 999; i++) {
		for (int j = 11; j <= 99; j++) {
			int a = i * (j % 10);
			int b = i * (j / 10);
			if (a > 999 || b > 999) continue;
			if (!contains(i) || !contains(j) || !contains(a) || !contains(b)) continue;
			int r = a + b * 10;
			if (r > 9999) break;
			if (!contains(r)) continue;
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
