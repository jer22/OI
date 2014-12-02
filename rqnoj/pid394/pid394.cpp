#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int number[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int table[1010][1010];

int calculate(int a) {
	if (!a)
		return 6;
	int r = 0;
	while (a) {
		r += number[a % 10];
		a /= 10;
	}
	return r;
}

int main() {
	freopen("pid394.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			table[i][j] = calculate(i) + calculate(j) + calculate(i + j) + 4;
		}
	}
	int cnt = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (table[i][j] == n) {
				cnt++;
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}
